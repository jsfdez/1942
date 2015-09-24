#pragma once

#include <QGraphicsObject>

class GraphicsHudObject : public QGraphicsObject
{
    Q_OBJECT

public:
    GraphicsHudObject(QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
        const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
