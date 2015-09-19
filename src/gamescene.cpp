#include "gamescene.h"

#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsPixmapItem>

#include "pixmapcache.h"
#include "graphicsbackgrounditem.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(0, 0, 600, 800, parent)
{
    addItem(new GraphicsBackgroundItem);

    const auto playerPixmap = PixmapCache::player();
    m_player = addPixmap(playerPixmap.copy(0, 0, playerPixmap.width() / 4,
        playerPixmap.height()));

    auto timer = new QTimer(this);
    timer->setInterval(1000 / 30); // 30 fps
    timer->setSingleShot(false);
    connect(timer, &QTimer::timeout, this, &GameScene::update);
    timer->start();
}

void GameScene::update()
{
    for(auto item : items())
    {
        item->update();
    }

    const auto playerPixmap = PixmapCache::player();
    m_playerFrame = (++m_playerFrame) % 3;
    m_player->setPixmap(playerPixmap.copy(
        m_playerFrame * playerPixmap.width() / 4, 0,
        playerPixmap.width() / 4, playerPixmap.height()));
}
