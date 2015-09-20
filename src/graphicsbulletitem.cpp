#include "graphicsbulletitem.h"

#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>

#include "pixmapcache.h"

GraphicsBulletItem::GraphicsBulletItem(const QPoint &pos,
    const QVector2D &direction, QGraphicsItem *parent)
: QGraphicsItem(parent)
, m_direction(direction)
{
    setPos(pos);
}

QRectF GraphicsBulletItem::boundingRect() const
{
    decltype(boundingRect()) rect = PixmapCache::bullet().rect();
    return rect;
}

void GraphicsBulletItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget*)
{
    if (scene()->sceneRect().contains(option->exposedRect.translated(pos())))
    {
        auto pixmap = PixmapCache::bullet();
        painter->drawPixmap(0, 0, pixmap);
    }
}

void GraphicsBulletItem::advance(int phase)
{
    if(phase == 1) return;

    auto p = pos();
    p += m_direction.toPoint() * 20;
    setPos(p);
}
