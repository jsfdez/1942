#include "graphicsplayerobject.h"

#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsDropShadowEffect>

#include "pixmapcache.h"

GraphicsPlayerObject::GraphicsPlayerObject(QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    auto effect = new QGraphicsDropShadowEffect;
    effect->setColor(QColor(0, 0, 0, 128));
    setGraphicsEffect(effect);
    setFlag(GraphicsPlayerObject::ItemIsFocusable, true);
    m_triggerTimer.setSingleShot(false);
    m_triggerTimer.setInterval(100);
}

QRectF GraphicsPlayerObject::boundingRect() const
{
    auto rect = PixmapCache::player().rect();
    rect.setWidth(rect.width() / 4);
    return rect;
}

void GraphicsPlayerObject::paint(QPainter *painter,
    const QStyleOptionGraphicsItem*, QWidget*)
{
    const auto asset = PixmapCache::player();
    const QRect source(m_frame * asset.width() / 4, 0, asset.width() / 4,
        asset.height());
    qDebug() << source;
    painter->drawPixmap({0, 0}, asset, source);
}

void GraphicsPlayerObject::advance(int phase)
{
    if (phase == 1) return;

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

    m_frame = ++m_frame % 3;
    update();
}

void GraphicsPlayerObject::trigger()
{
    if (m_triggerTimer.isActive())
        return;

    QVector<QPair<QPoint, QVector2D>> bullets(m_cannonCount);
    switch(m_cannonCount)
    {
    case 2:
        bullets[0].first = QPoint(pos().x() + boundingRect().width() / 4,
            pos().y() - 5);
        bullets[0].second = QVector2D(0.f, -1.f);
        bullets[1].first = QPoint(pos().x() + boundingRect().width() * 3 / 4,
            pos().y() - 5);
        bullets[1].second = QVector2D(0.f, -1.f);
        break;
    default:
        qFatal("Invalid cannon count");
    }
    emit cannonTriggered(bullets);
}

void GraphicsPlayerObject::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        m_keys.insert(event->key());
        break;
    case Qt::Key_Space:
        trigger();
        m_triggerTimer.start();
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
        m_keys.remove(event->key());
        event->accept();
        break;
    case Qt::Key_Space:
        m_triggerTimer.stop();
        event->accept();
    default:
        event->ignore();
    }
}
