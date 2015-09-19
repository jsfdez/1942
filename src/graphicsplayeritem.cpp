#include "graphicsplayeritem.h"

#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsDropShadowEffect>

#include "pixmapcache.h"

GraphicsPlayerItem::GraphicsPlayerItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    auto effect = new QGraphicsDropShadowEffect;
    effect->setColor(Qt::black);
    setGraphicsEffect(effect);
    setFlag(GraphicsPlayerItem::ItemIsFocusable, true);
}

QRectF GraphicsPlayerItem::boundingRect() const
{
    auto rect = PixmapCache::player().rect();
    rect.setWidth(rect.width() / 4);
    return rect;
}

void GraphicsPlayerItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
    const auto asset = PixmapCache::player();
    const QRect source(m_frame * asset.width() / 4, 0, asset.width() / 4,
        asset.height());
    painter->drawPixmap({0, 0}, asset, source);
}

void GraphicsPlayerItem::advance(int phase)
{
    auto p = pos();
    const auto sceneRect = scene()->sceneRect();

    // Horizontal movement
    if (m_keys.contains(Qt::Key_Left) && m_keys.contains(Qt::Key_Right));
    else if (m_keys.contains(Qt::Key_Left))
        p.setX(qMax(p.x() - k_speed, sceneRect.x()));
    else if (m_keys.contains(Qt::Key_Right))
    {
        const auto right = sceneRect.x() + sceneRect.width()
            - boundingRect().width();
        p.setX(qMin(p.x() + k_speed, right));
    }

    // Vertical movement
    if (m_keys.contains(Qt::Key_Up) && m_keys.contains(Qt::Key_Down));
    else if (m_keys.contains(Qt::Key_Up))
        p.setY(qMax(p.y() - k_speed, sceneRect.y()));
    else if (m_keys.contains(Qt::Key_Down))
    {
        const auto bottom = sceneRect.y() + sceneRect.height()
            - boundingRect().height();
        p.setY(qMin(p.y() + k_speed, bottom));
    }

    setPos(p);
    m_frame = phase % 3;
}

void GraphicsPlayerItem::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        m_keys.insert(event->key());
        break;
    case Qt::Key_S:
        graphicsEffect()->setEnabled(!graphicsEffect()->isEnabled());
        event->accept();
        break;
    default:
        event->ignore();
    }
}

void GraphicsPlayerItem::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        m_keys.remove(event->key());
        event->accept();
        break;
    default:
        event->ignore();
    }
}

