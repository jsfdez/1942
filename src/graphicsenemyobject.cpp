#include "graphicsenemyobject.h"

#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>

#include "defines.h"
#include "gamescene.h"
#include "pixmapcache.h"

GraphicsEnemyObject::GraphicsEnemyObject(EnemyType type,
	QEasingCurve easingCurve, bool inverted, QGraphicsItem* parent)
: AbstractGraphicsPlaneObject(parent)
, m_curve(easingCurve)
, m_inverted(inverted)
, k_triggerTicks((qrand() % 1500 + 500) / FPS)
, m_enemyType(type)
{
	m_cannonCount = 1;
    setVisible(false);
    switch(type)
    {
    case EnemyType::Green:
        m_pixmap = &PixmapCache::greenEnemy;
        m_health = ENEMY_HEALTH;
        break;
    case EnemyType::White:
        m_pixmap = &PixmapCache::whiteEnemy;
        m_health = ENEMY_HEALTH;
        break;
    case EnemyType::Boss:
        m_pixmap  = &PixmapCache::bossEnemy;
        m_health = BOSS_HEALTH;
        m_cannonCount = 2;
        break;
    }

    m_triggerPendingTicks = k_triggerTicks;
}

void GraphicsEnemyObject::move()
{
    if (!isVisible()) setVisible(true);

    if(m_time > 1.0f)
        deleteLater();

    const auto height = scene()->sceneRect().height() - HUD_HEIGHT;
    const auto planeWidth = boundingRect().width();
    const auto width = scene()->sceneRect().width() - planeWidth;
    const auto planeHeight = boundingRect().height();
    auto x = m_curve.valueForProgress(m_time) * width - planeWidth / 2;
    if (m_inverted)
        x = width - x;
    setPos(x, m_time * (height + planeHeight + HUD_HEIGHT));

    m_time += 0.005f;
    if(--m_triggerPendingTicks == 0)
    {
        trigger();
        m_triggerPendingTicks = k_triggerTicks;
    }
}

int GraphicsEnemyObject::type() const
{
    return GameScene::EnemyType;
}

QRectF GraphicsEnemyObject::boundingRect() const
{
    auto rect = AbstractGraphicsPlaneObject::boundingRect();
    rect.setSize(rect.size());
    return rect;
}

GraphicsEnemyObject::EnemyType GraphicsEnemyObject::enemyType() const
{
    return m_enemyType;
}

QVector2D GraphicsEnemyObject::direction() const
{
    return QVector2D(0.f, 1.f);
}

QPixmap GraphicsEnemyObject::pixmap() const
{
    return m_pixmap();
}
