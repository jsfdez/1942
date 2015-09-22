#pragma once

#include <QVector2D>
#include <QGraphicsObject>

class AbstractGraphicsPlaneObject : public QGraphicsObject
{
    Q_OBJECT

public:
    enum class Status
    {
        Alive,
        Death,
    };

    AbstractGraphicsPlaneObject(QGraphicsItem* parent = nullptr);

    Status status() const;

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
        const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void advance(int phase) override;

public slots:
    void impact(qint32 damage);

signals:
    void exploded();
    void cannonTriggered(QVector<QPair<QPoint, QVector2D>> bullets);

protected:
    virtual QPixmap pixmap() const = 0;
    virtual void move() = 0;
    virtual QVector2D direction() const = 0;
    virtual void trigger();

    Status m_status = Status::Alive;
    qint32 m_health = 200;
    quint8 m_cannonCount = 2;
    quint8 k_speed = 10;
    quint8 m_frame = 0;
};
