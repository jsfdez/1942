#ifndef GRAPHICSPLAYERITEM_H
#define GRAPHICSPLAYERITEM_H

#include <QSet>
#include <QGraphicsItem>

class GraphicsPlayerItem : public QGraphicsItem
{
public:
    GraphicsPlayerItem(QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
        const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual void advance(int phase) override;

private:
    const quint8 k_speed = 5;
    quint8 m_frame = 0;
    QSet<std::underlying_type<Qt::Key>::type> m_keys;

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
};

#endif // GRAPHICSPLAYERITEM_H
