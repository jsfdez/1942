#pragma once

#include <QGraphicsObject>

class GraphicsHudObject : public QGraphicsObject
{
    Q_OBJECT

    Q_PROPERTY(quint32 score READ score RESET resetScore)
public:
    GraphicsHudObject(QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
        const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void addScore(quint32 points);
    quint32 score() const;
    void resetScore();

signals:
    void scoreChanged(quint32 current);

private:
    quint32 m_score = 0;

private slots:
    void update();
};
