#include "graphicsbackgrounditem.h"

#include <QGraphicsScene>

#include <QPainter>

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
    const QStyleOptionGraphicsItem*, QWidget*)
{
    const auto background = PixmapCache::sea();
    Q_ASSERT_X(!background.isNull(), "load", "Cannot load background image");
    auto rect = scene()->sceneRect();
    m_offset = (++m_offset) % background.height();
    QPoint offset(0, m_offset);
    painter->drawTiledPixmap(rect, background, offset);
}

