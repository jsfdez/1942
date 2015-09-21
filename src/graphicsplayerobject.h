#ifndef GRAPHICSPLAYERITEM_H
#define GRAPHICSPLAYERITEM_H

#include <QSet>
#include <QTimer>
#include <QVector2D>
#include <QGraphicsItem>

class GraphicsPlayerObject : public QGraphicsObject
{
    Q_OBJECT

public:
    GraphicsPlayerObject(QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
        const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual void advance(int phase) override;

signals:
    void cannonTriggered(QVector<QPair<QPoint, QVector2D>> bullets);

protected:
    void trigger();

	quint8 m_frame = 0;

private:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    const quint8 k_speed = 5;
    quint8 m_cannonCount = 2;
    QSet<std::underlying_type<Qt::Key>::type> m_keys;
    QTimer m_triggerTimer;
};

#endif // GRAPHICSPLAYERITEM_H
