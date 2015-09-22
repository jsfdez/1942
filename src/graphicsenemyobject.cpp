#include "graphicsenemyobject.h"

#include <QDebug>
#include <QPainter>
#include <QKeyEvent>

#include "gamescene.h"
#include "pixmapcache.h"

GraphicsEnemyObject::GraphicsEnemyObject(EnemyType type,
	QEasingCurve easingCurve, bool inverted, QGraphicsItem* parent)
: GraphicsPlayerObject(parent)
, m_easingCurve(easingCurve)
, m_inverted(inverted)
{
    setVisible(false);
    switch(type)
    {
    case EnemyType::Green: m_pixmap = &PixmapCache::greenEnemy; break;
    case EnemyType::White: m_pixmap = &PixmapCache::whiteEnemy; break;
    case EnemyType::Boss: m_pixmap  = &PixmapCache::bossEnemy;  break;
    }

	setFlag(GraphicsPlayerObject::ItemIsFocusable, false);
}

QRectF GraphicsEnemyObject::boundingRect() const
{
    auto rect = m_pixmap().rect();
	rect.setWidth(rect.width() / 4);
	return rect;
}

void GraphicsEnemyObject::paint(QPainter* painter,
	const QStyleOptionGraphicsItem*, QWidget*)
{
    switch(status())
    {
    case Status::Alive:
    {
        const auto asset = m_pixmap();
        const QRect source(m_frame * asset.width() / 4, 0, asset.width() / 4,
                           asset.height());
        painter->drawPixmap({0, 0}, asset, source);
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
}

void GraphicsEnemyObject::advance(int phase)
{
	if(phase == 1)
	{
		GraphicsPlayerObject::advance(phase);
		m_time += 0.005f;
        if(m_time > 1.0f)
            deleteLater();
	}
	else
	{
        if (!isVisible()) setVisible(true);

        const auto width = scene()->sceneRect().width();
        const auto height = scene()->sceneRect().height();
        const auto planeWidth = boundingRect().width();
        const auto planeHeight = boundingRect().height();
        auto x = m_easingCurve.valueForProgress(m_time) * width
            - planeWidth / 2;
        if (m_inverted)
            x = width - x;
        setPos(x, m_time * (height + planeHeight));
	}
}

int GraphicsEnemyObject::type() const
{
    return GameScene::EnemyType;
}

void GraphicsEnemyObject::keyPressEvent(QKeyEvent* event)
{
	event->ignore();
}

void GraphicsEnemyObject::keyReleaseEvent(QKeyEvent* event)
{
	event->ignore();
}
