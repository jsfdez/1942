#include "graphicsplayerobject.h"

#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsEffect>

#include "gamescene.h"
#include "pixmapcache.h"

GraphicsPlayerObject::GraphicsPlayerObject(QGraphicsItem *parent)
: AbstractGraphicsPlaneObject(parent)
, k_triggerTicks(100 / GameScene::FPS)
{
    m_health = 10000;
    setFlag(GraphicsPlayerObject::ItemIsFocusable, true);
}

void GraphicsPlayerObject::move()
{
    auto p = pos();
    const auto sceneRect = scene()->sceneRect();

    m_triggerPendingTicks = qMax(0, --m_triggerPendingTicks);

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

    if(m_keys.contains(Qt::Key_Space))
        trigger();

    setPos(p);
}

int GraphicsPlayerObject::type() const
{
    return GameScene::PlayerType;
}

void GraphicsPlayerObject::pause()
{

}

void GraphicsPlayerObject::resume()
{

}

QVector2D GraphicsPlayerObject::direction() const
{
    return QVector2D(0.f, -1.f);
}

QPixmap GraphicsPlayerObject::pixmap() const
{
    return PixmapCache::player();
}

void GraphicsPlayerObject::trigger()
{
    if (m_triggerPendingTicks == 0)
    {
        AbstractGraphicsPlaneObject::trigger();
        m_triggerPendingTicks = k_triggerTicks;
    }
}

void GraphicsPlayerObject::focusInEvent(QFocusEvent *)
{
    emit focusReceived();
}

void GraphicsPlayerObject::focusOutEvent(QFocusEvent *)
{
    emit focusLost();
}

void GraphicsPlayerObject::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Space:
        m_keys.insert(event->key());
        event->accept();
        break;
    case Qt::Key_S:
        graphicsEffect()->setEnabled(!graphicsEffect()->isEnabled());
        event->accept();
        break;
    default:
        event->ignore();
    }
}

void GraphicsPlayerObject::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Space:
        m_keys.remove(event->key());
        event->accept();
        break;
    default:
        event->ignore();
    }
}
