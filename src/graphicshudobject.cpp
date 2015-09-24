#include "graphicshudobject.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "gamescene.h"
#include "pixmapcache.h"

GraphicsHudObject::GraphicsHudObject(QGraphicsItem *parent)
: QGraphicsObject(parent)
{
    setZValue(1);
    connect(this, SIGNAL(scoreChanged(quint32)), this, SLOT(update()));
}

QRectF GraphicsHudObject::boundingRect() const
{
    return QRectF(0, 0, scene()->sceneRect().width(), GameScene::HudHeight);
}

void GraphicsHudObject::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->fillRect(option->rect, Qt::black);
    painter->drawPixmap(0, 0, PixmapCache::hudNumber(m_score));
}

void GraphicsHudObject::addScore(quint32 points)
{
    if(points)
    {
        m_score += points;
        emit scoreChanged(m_score);
    }
}

quint32 GraphicsHudObject::score() const
{
    return m_score;
}

void GraphicsHudObject::resetScore()
{
    if(m_score != 0)
    {
        m_score = 0;
        emit scoreChanged(m_score);
    }
}

void GraphicsHudObject::update()
{
    QGraphicsObject::update();
}

