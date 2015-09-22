#include "graphicsenemyobject.h"

#include <QDebug>
#include <QPainter>
#include <QKeyEvent>

#include "gamescene.h"
#include "pixmapcache.h"

GraphicsEnemyObject::GraphicsEnemyObject(EnemyType type,
	QEasingCurve easingCurve, bool inverted, QGraphicsItem* parent)
: AbstractGraphicsPlaneObject(parent)
, m_curve(easingCurve)
, m_inverted(inverted)
{
    setVisible(false);
    switch(type)
    {
    case EnemyType::Green: m_pixmap = &PixmapCache::greenEnemy; break;
    case EnemyType::White: m_pixmap = &PixmapCache::whiteEnemy; break;
    case EnemyType::Boss: m_pixmap  = &PixmapCache::bossEnemy;  break;
    }
}

void GraphicsEnemyObject::move()
{
    if (!isVisible()) setVisible(true);

    if(m_time > 1.0f)
        deleteLater();

    const auto height = scene()->sceneRect().height();
    const auto planeWidth = boundingRect().width();
    const auto width = scene()->sceneRect().width() - planeWidth;
    const auto planeHeight = boundingRect().height();
    auto x = m_curve.valueForProgress(m_time) * width - planeWidth / 2;
    if (m_inverted)
        x = width - x;
    setPos(x, m_time * (height + planeHeight));

    m_time += 0.005f;
}

int GraphicsEnemyObject::type() const
{
    return GameScene::EnemyType;
}

QPixmap GraphicsEnemyObject::pixmap() const
{
    return m_pixmap();
}
