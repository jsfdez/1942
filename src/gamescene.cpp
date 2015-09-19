#include "gamescene.h"

#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsPixmapItem>

#include "pixmapcache.h"
#include "graphicsbulletitem.h"
#include "graphicsplayerobject.h"
#include "graphicsbackgrounditem.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(0, 0, 600, 800, parent)
    , m_player(new GraphicsPlayerObject)
{
    addItem(new GraphicsBackgroundItem);
    {
        const auto playerSize = m_player->boundingRect().size();
        QPointF pos{
            sceneRect().width() / 2 - playerSize.width() / 2,
            sceneRect().height() - playerSize.height(),
        };
        m_player->setPos(pos);
    }
    addItem(m_player);
    connect(m_player, &GraphicsPlayerObject::cannonTriggered, this,
        &GameScene::planeShot);

    setFocusItem(m_player);

    auto timer = new QTimer(this);
    timer->setInterval(1000 / 30); // 30 fps
    timer->setSingleShot(false);
    connect(timer, &QTimer::timeout, this, &GameScene::update);
    timer->start();
}

void GameScene::update()
{
    qDebug() << "Total items:" << items().size();
    for(auto item : items())
    {
        m_phase = std::max(++m_phase, 0);
        item->advance(m_phase);
        item->update();
    }
}

void GameScene::planeShot(QVector<QPair<QPoint, QVector2D>> bullets)
{
    for(auto& pair : bullets)
    {
        auto bullet = new GraphicsBulletItem(pair.first, pair.second);
        addItem(bullet);
    }
}
