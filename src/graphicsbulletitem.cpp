#include "graphicsbulletitem.h"

#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>

#include "gamescene.h"
#include "pixmapcache.h"

GraphicsBulletItem::GraphicsBulletItem(const QPoint &pos,
    const QVector2D &direction, bool playerBullet, QGraphicsItem *parent)
: QGraphicsItem(parent)
, m_direction(direction)
, m_playerBullet(playerBullet)
{
    setPos(pos);
}

int GraphicsBulletItem::type() const
{
    return m_playerBullet ? GameScene::BulletType : GameScene::EnemyBulletType;
}

QRectF GraphicsBulletItem::boundingRect() const
{
    auto pixmap = m_playerBullet ? PixmapCache::bullet()
        : PixmapCache::enemyBullet();
    decltype(boundingRect()) rect = pixmap.rect();
    return rect;
}

void GraphicsBulletItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget*)
{
    if (scene()->sceneRect().contains(option->exposedRect.translated(pos())))
    {
        auto pixmap = m_playerBullet ? PixmapCache::bullet()
            : PixmapCache::enemyBullet();
        painter->drawPixmap(0, 0, pixmap);
    }
}

void GraphicsBulletItem::advance(int phase)
{
	if(phase == 1)
	{
		auto p = pos();
		p += m_direction.toPoint() * k_speed;
		setPos(p);
    }
}
