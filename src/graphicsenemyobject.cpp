#include "graphicsenemyobject.h"

#include <QPainter>
#include <QKeyEvent>

#include "pixmapcache.h"

GraphicsEnemyObject::GraphicsEnemyObject(EnemyType type, QGraphicsItem* parent)
: GraphicsPlayerObject(parent)
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
    const auto asset = m_pixmap();
	const QRect source(m_frame * asset.width() / 4, 0, asset.width() / 4,
		asset.height());
	painter->drawPixmap({0, 0}, asset, source);
}

void GraphicsEnemyObject::advance(int phase)
{
	if(phase == 1)
		GraphicsPlayerObject::advance(phase);
}

void GraphicsEnemyObject::keyPressEvent(QKeyEvent* event)
{
	event->ignore();
}

void GraphicsEnemyObject::keyReleaseEvent(QKeyEvent* event)
{
	event->ignore();
}
