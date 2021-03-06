#include "graphicshudobject.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "gamescene.h"
#include "pixmapcache.h"

GraphicsHudObject::GraphicsHudObject(quint32 maxHealth, QGraphicsItem *parent)
: QGraphicsObject(parent)
, m_health(maxHealth)
, m_maxHealth(maxHealth)
{
    setZValue(1);
}

QRectF GraphicsHudObject::boundingRect() const
{
    return QRectF(0, 0, scene()->sceneRect().width(), HUD_HEIGHT);
}

void GraphicsHudObject::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->fillRect(option->rect, Qt::black);
    const auto scorePixmap = PixmapCache::hudNumber(m_score);
    painter->drawPixmap(0, 0, scorePixmap);

    QRectF healthBarRect(scorePixmap.rect().right() + 2, 3,
        scorePixmap.rect().width(), HUD_HEIGHT - 6);
    {
        painter->save();
        const auto ratio = static_cast<float>(m_health) / m_maxHealth;
        QBrush brush(ratio < 0.25f ? Qt::red : Qt::green);
        painter->setBrush(brush);
        painter->drawRect(healthBarRect.adjusted(0, 0,
            -healthBarRect.width() + healthBarRect.width() * ratio, 0));
        painter->restore();

        painter->save();
        QPen pen(Qt::white, 2);
        painter->setPen(pen);
        painter->drawRect(healthBarRect);
        painter->restore();
    }

    for(quint32 i = 0u; i < m_lifesRemaining; i++)
    {
        const auto pixmap = PixmapCache::playerLife();
        painter->drawPixmap(
            sceneBoundingRect().width() - pixmap.width() * (i + 1), 0, pixmap);
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
        update();
    }
}

void GraphicsHudObject::addScore(quint32 points)
{
    if(points)
    {
        m_score += points;
        emit scoreChanged(m_score);
    }
}

void GraphicsHudObject::setHealth(quint32 health)
{
    if(m_health != health)
    {
        m_health = health;
        emit healthChanged(m_health);
        update();
    }
}

void GraphicsHudObject::playerDeath()
{
    if(--m_lifesRemaining == 0)
    {
        emit gameOver(m_score);
        update();
    }
}

quint32 GraphicsHudObject::health() const
{
    return m_health;
}
