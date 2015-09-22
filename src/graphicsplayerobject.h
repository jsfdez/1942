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
    enum class Status
    {
        Alive,
        Death,
    };

    GraphicsPlayerObject(QGraphicsItem *parent = nullptr);

    Status status() const;

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
        const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual void advance(int phase) override;
    virtual int type() const override;

public slots:
    void impact(quint32 damage);

signals:
    void cannonTriggered(QVector<QPair<QPoint, QVector2D>> bullets);
    void exploded();

protected:
    void trigger();

	quint8 m_frame = 0;

private:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

	const quint8 k_speed = 10;
    quint8 m_cannonCount = 2;
    QSet<std::underlying_type<Qt::Key>::type> m_keys;
    QTimer m_triggerTimer;
    Status m_status = Status::Alive;
    qint32 m_health = 300;
};

#endif // GRAPHICSPLAYERITEM_H
