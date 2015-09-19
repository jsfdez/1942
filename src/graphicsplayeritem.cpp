#include "graphicsplayeritem.h"

#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsScene>

#include "pixmapcache.h"

GraphicsPlayerItem::GraphicsPlayerItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setFlag(GraphicsPlayerItem::ItemIsFocusable, true);
}

QRectF GraphicsPlayerItem::boundingRect() const
{
    const auto player = PixmapCache::player();
    QRectF rect{
        -player.rect().width() / 8.0f,
        -player.rect().height() / 2.0f,
        player.rect().width() / 4.0f,
        static_cast<qreal>(player.rect().height()),
    };
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
    if (m_keys.contains(Qt::Key_Left) && m_keys.contains(Qt::Key_Right));
    else if (m_keys.contains(Qt::Key_Left))
        setPos(qMax(scene()->sceneRect().x(), pos().x() - k_speed), pos().y());
    else if (m_keys.contains(Qt::Key_Right))
    {
        setPos(qMin(scene()->sceneRect().width() - boundingRect().width(),
            pos().x() + k_speed), pos().y());
    }

    if (m_keys.contains(Qt::Key_Up) && m_keys.contains(Qt::Key_Down));
    else if (m_keys.contains(Qt::Key_Up))
        setPos(pos().x(), qMax(scene()->sceneRect().x(), pos().y() - k_speed));
    else if (m_keys.contains(Qt::Key_Down))
    {
        setPos(pos().x(),
            qMin(scene()->sceneRect().height() - boundingRect().height(),
            pos().y() + k_speed));
    }

    m_frame = phase % 3;
}

void GraphicsPlayerItem::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Pressed key:" << event->key() << Qt::LeftArrow;
    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        m_keys.insert(event->key());
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

