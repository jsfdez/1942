#include "graphicsenemyobject.h"

#include <QDebug>
#include <QPainter>
#include <QKeyEvent>

#include "gamescene.h"
#include "pixmapcache.h"

GraphicsEnemyObject::GraphicsEnemyObject(EnemyType type,
	QEasingCurve easingCurve, QGraphicsItem* parent)
: GraphicsPlayerObject(parent)
, m_easingCurve(easingCurve)
{
    switch(type)
    {
    case EnemyType::Green: m_pixmap = &PixmapCache::greenEnemy; break;
    case EnemyType::White: m_pixmap = &PixmapCache::whiteEnemy; break;
    case EnemyType::Boss: m_pixmap  = &PixmapCache::bossEnemy;  break;
    }

	setFlag(GraphicsPlayerObject::ItemIsFocusable, false);
}

QRectF GraphicsEnemyObject::boundingRect() const
{
    auto rect = m_pixmap().rect();
	rect.setWidth(rect.width() / 4);
	return rect;
}

void GraphicsEnemyObject::paint(QPainter* painter,
	const QStyleOptionGraphicsItem*, QWidget*)
{
    switch(status())
    {
    case Status::Alive:
    {
        const auto asset = m_pixmap();
        const QRect source(m_frame * asset.width() / 4, 0, asset.width() / 4,
                           asset.height());
        painter->drawPixmap({0, 0}, asset, source);
        break;
    }
    case Status::Death:
    {
        const auto asset = PixmapCache::explosion();
        const QRect source(m_frame * asset.width() / 6, 0, asset.width() / 6,
                           asset.height());
        painter->drawPixmap(boundingRect(), asset, source);
        break;
    }
    }
}

void GraphicsEnemyObject::advance(int phase)
{
	if(phase == 1)
	{
		GraphicsPlayerObject::advance(phase);
		m_time += 0.005f;
	}
	else
	{
		const auto rect = scene()->sceneRect();
		setPos(m_easingCurve.valueForProgress(m_time) * rect.width(),
			m_time * rect.height());
	}
}

int GraphicsEnemyObject::type() const
{
    return GameScene::EnemyType;
}

void GraphicsEnemyObject::keyPressEvent(QKeyEvent* event)
{
	event->ignore();
}

void GraphicsEnemyObject::keyReleaseEvent(QKeyEvent* event)
{
	event->ignore();
}
