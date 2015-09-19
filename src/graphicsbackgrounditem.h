#ifndef GRAPHICSBACKGROUNDITEM_H
#define GRAPHICSBACKGROUNDITEM_H

#include <QGraphicsItem>

class GraphicsBackgroundItem : public QGraphicsItem
{
public:
    GraphicsBackgroundItem(QGraphicsItem* parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
        const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    quint8 m_offset = 0;
};

#endif // GRAPHICSBACKGROUNDITEM_H
