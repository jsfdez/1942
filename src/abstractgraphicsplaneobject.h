#pragma once

#include <QTimer>
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

    void blink();

    bool isInvencible() const;
    void setInvencible(bool value);

    quint32 health() const;

public slots:
    void impact(qint32 damage);

signals:
    void invencibleChanged(bool value);
    void exploded();
    void damaged(quint32 health);
    void cannonTriggered(QVector<QPair<QPoint, QVector2D>> bullets);

protected:
    virtual QPixmap pixmap() const = 0;
    virtual void move() = 0;
    virtual QVector2D direction() const = 0;
    virtual void trigger();

    Status m_status = Status::Alive;
    qint32 m_health = 200;
    qint32 m_maxHealth;
    quint8 m_cannonCount = 2;
    quint8 k_speed = 10;
    quint8 m_frame = 0;

private:
	quint8 m_blinkCount = 0;
    bool m_invencible = false;
};
