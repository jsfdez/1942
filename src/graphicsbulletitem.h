#ifndef GRAPHICSBULLETITEM_H
#define GRAPHICSBULLETITEM_H

#include <QVector2D>
#include <QGraphicsItem>

class GraphicsBulletItem : public QGraphicsItem
{
public:
    GraphicsBulletItem(const QPoint &pos, const QVector2D &direction,
        QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
        const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void advance(int phase) override;

private:
    QVector2D m_direction;
};

#endif // GRAPHICSBULLETITEM_H
