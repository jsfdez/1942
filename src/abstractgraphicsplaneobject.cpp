#include "abstractgraphicsplaneobject.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsDropShadowEffect>

#include "gamescene.h"
#include "pixmapcache.h"

AbstractGraphicsPlaneObject::AbstractGraphicsPlaneObject(QGraphicsItem *parent)
: QGraphicsObject(parent)
{
    auto effect = new QGraphicsDropShadowEffect;
    effect->setColor(QColor(0, 0, 0, 128));
    setGraphicsEffect(effect);
	m_blinkTimer.setInterval(100);
	m_blinkTimer.setSingleShot(false);
	connect(&m_blinkTimer, &QTimer::timeout, [&]()
	{
        if(--m_blinkCount == 0)
			m_blinkTimer.stop();
	});
}

AbstractGraphicsPlaneObject::Status AbstractGraphicsPlaneObject::status() const
{
    return m_status;
}

QRectF AbstractGraphicsPlaneObject::boundingRect() const
{
    auto rect = pixmap().rect();
    rect.setWidth(rect.width() / 4);
    return rect;
}

void AbstractGraphicsPlaneObject::paint(QPainter *painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->save();
    const auto sceneTopLeft = mapFromScene(0, GameScene::HudHeight);
    const auto sceneSize = scene()->sceneRect().size().expandedTo(QSizeF(0,
        -GameScene::HudHeight));
    QRectF clipRect(sceneTopLeft, sceneSize);
    painter->setClipRect(clipRect);
    switch(m_status)
    {
    case Status::Alive:
    {
        const auto asset = pixmap();
		auto frame = m_frame * asset.width() / 4;
		if(m_blinkCount % 2 != 0)
			frame = 3 * asset.width() / 4;
		const QRect source(frame, 0, asset.width() / 4, asset.height());
        painter->drawPixmap(boundingRect(), asset, source);
        break;
    }
    case Status::Death:
    {
        const auto asset = PixmapCache::explosion();
        const QRect source(m_frame * asset.width() / 6, 0, asset.width() / 6,
                           asset.height());
        painter->drawPixmap(boundingRect(), asset, source);
        break;
    }
    }
    painter->restore();
}

void AbstractGraphicsPlaneObject::advance(int phase)
{
    if(phase == 1)
    {
        if (m_status == Status::Alive)
		{
			m_frame = ++m_frame % 3;
		}
		else if (m_frame == 6)
        {
            emit exploded();
            deleteLater();
        }
        else
            ++m_frame;
        update();
    }
    else if (status() == Status::Alive) move();
}

void AbstractGraphicsPlaneObject::impact(qint32 damage)
{
    m_health = qMax(0, m_health - damage);
    if(!m_health)
    {
        m_status = Status::Death;
        graphicsEffect()->setEnabled(false);
        m_frame = 0;
    }
	else
	{
		m_blinkTimer.start();
		m_blinkCount = k_maxBlink;
	}
    emit damaged(m_health);
}

void AbstractGraphicsPlaneObject::trigger()
{
    const auto dir = direction();
    const auto x = pos().x() - 1;
	const auto width = boundingRect().size().width();
	const auto height = boundingRect().size().height();
    const auto dirY = dir.y() * height / 2;
    const auto y = sceneBoundingRect().center().y() + dirY;
    QVector<QPair<QPoint, QVector2D>> bullets(m_cannonCount);
    switch(m_cannonCount)
    {
	case 1:
	{
        QPoint point(x + width / 2, y/* + dirY*/);
		bullets[0].first = point;
		bullets[0].second = dir;
		break;
	}
    case 2:
        bullets[0].first = QPoint(x + width / 4, y/* + dirY*/);
        bullets[0].second = dir;
        bullets[1].first = QPoint(x + width * 3 / 4, y/* + dirY*/);
        bullets[1].second = dir;
        break;
    default:
        qFatal("Invalid cannon count");
    }
    emit cannonTriggered(bullets);
}

