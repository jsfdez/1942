#include "abstractgraphicsplaneobject.h"

#include <QPainter>
#include <QGraphicsDropShadowEffect>

#include "pixmapcache.h"

AbstractGraphicsPlaneObject::AbstractGraphicsPlaneObject(QGraphicsItem *parent)
: QGraphicsObject(parent)
{
    auto effect = new QGraphicsDropShadowEffect;
    effect->setColor(QColor(0, 0, 0, 128));
    setGraphicsEffect(effect);
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
    switch(m_status)
    {
    case Status::Alive:
    {
        const auto asset = pixmap();
        const QRect source(m_frame * asset.width() / 4, 0, asset.width() / 4,
                           asset.height());
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
}

void AbstractGraphicsPlaneObject::advance(int phase)
{
    if(phase == 1)
    {
        if (m_status == Status::Alive)
            m_frame = ++m_frame % 3;
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
}

void AbstractGraphicsPlaneObject::trigger()
{
    const auto dir = direction();
    QVector<QPair<QPoint, QVector2D>> bullets(m_cannonCount);
    switch(m_cannonCount)
    {
    case 2:
        bullets[0].first = QPoint(pos().x() + boundingRect().width() / 4,
            pos().y() + dir.y() * 20);
        bullets[0].second = dir;
        bullets[1].first = QPoint(pos().x() + boundingRect().width() * 3 / 4,
            pos().y() + dir.y() * 20);
        bullets[1].second = dir;
        break;
    default:
        qFatal("Invalid cannon count");
    }
    emit cannonTriggered(bullets);
}

