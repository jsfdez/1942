#include "graphicsbackgrounditem.h"

#include <QGraphicsScene>

#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "gamescene.h"
#include "pixmapcache.h"

GraphicsBackgroundItem::GraphicsBackgroundItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
}

QRectF GraphicsBackgroundItem::boundingRect() const
{
    return scene()->sceneRect();
}

void GraphicsBackgroundItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget*)
{
    const auto background = PixmapCache::sea();
    Q_ASSERT_X(!background.isNull(), "load", "Cannot load background image");
    const auto rect = option->exposedRect;
    QPoint offset(0, background.height() - m_offset);
    painter->drawTiledPixmap(rect, background, offset);
}

void GraphicsBackgroundItem::advance(int phase)
{
	if(phase == 0)
        m_offset = ++m_offset % PixmapCache::sea().height();
    else update();
}

int GraphicsBackgroundItem::type() const
{
    return GameScene::BackgroundType;
}
