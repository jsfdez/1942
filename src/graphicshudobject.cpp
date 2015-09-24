#include "graphicshudobject.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "gamescene.h"

GraphicsHudObject::GraphicsHudObject(QGraphicsItem *parent)
: QGraphicsObject(parent)
{
    setZValue(1);
}

QRectF GraphicsHudObject::boundingRect() const
{
    return QRectF(0, 0, scene()->sceneRect().width(), GameScene::HudHeight);
}

void GraphicsHudObject::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->fillRect(option->rect, Qt::black);
}

