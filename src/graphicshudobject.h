#pragma once

#include <QGraphicsObject>

class GraphicsHudObject : public QGraphicsObject
{
    Q_OBJECT

    Q_PROPERTY(quint32 score READ score RESET resetScore NOTIFY scoreChanged)
    Q_PROPERTY(quint32 health READ health NOTIFY scoreChanged)
public:
    GraphicsHudObject(quint32 maxHealth, QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
        const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    quint32 score() const;
    void resetScore();

    quint32 health() const;

public slots:
    void addScore(quint32 points);
    void setHealth(quint32 health);

signals:
    void scoreChanged(quint32 current);
    void healthChanged(quint32 health);

private:
    quint32 m_score = 0;
    quint32 m_health;
    quint32 m_maxHealth;

private slots:
    void update();
};
