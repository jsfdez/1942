#include "gamescene.h"

#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsPixmapItem>

#include "pixmapcache.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(0, 0, 600, 800, parent)
{
    auto seaBackground = PixmapCache::sea();
    Q_ASSERT(!seaBackground.isNull());

    QPixmap background(sceneRect().size().toSize());
    {
        QPainter painter(&background);
        QRect rect(0, 0, painter.device()->width(), painter.device()->height());
        painter.drawTiledPixmap(rect, seaBackground);
    }
    m_background = addPixmap(background);

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
    auto currentPixmap = m_background->pixmap();
    {
        const auto background = PixmapCache::sea();
        const auto bgHeight = background.height();
        QPainter painter(&currentPixmap);
        QRect rect(0, 0, painter.device()->width(), painter.device()->height());
        m_backgroundOffset = (m_backgroundOffset + 1) % bgHeight;
        QPoint offset(0, bgHeight - m_backgroundOffset);
        painter.drawTiledPixmap(rect, background, offset);
    }
    m_background->setPixmap(currentPixmap);
    const auto playerPixmap = PixmapCache::player();
    m_playerFrame = (++m_playerFrame) % 3;
    m_player->setPixmap(playerPixmap.copy(
        m_playerFrame * playerPixmap.width() / 4, 0,
        playerPixmap.width() / 4, playerPixmap.height()));
}
