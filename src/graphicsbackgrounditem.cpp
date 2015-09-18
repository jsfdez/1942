#include "graphicsbackgrounditem.h"

#include <QGraphicsScene>

#include "pixmapcache.h"

GraphicsBackgroundItem::GraphicsBackgroundItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
}

QRectF GraphicsBackgroundItem::boundingRect() const
{
    return scene()->sceneRect();
}

void GraphicsBackgroundItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

