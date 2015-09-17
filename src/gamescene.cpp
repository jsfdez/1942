#include "gamescene.h"

#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsPixmapItem>

static QScopedPointer<QPixmap> s_background;

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(0, 0, 600, 800, parent)
{
    if (s_background.isNull())
        s_background.reset(new QPixmap(":/asset/sea.png"));
    Q_ASSERT(!s_background.isNull() && !s_background->isNull());

    QPixmap background(sceneRect().size().toSize());
    {
        QPainter painter(&background);
        QRect rect(0, 0, painter.device()->width(), painter.device()->height());
        painter.drawTiledPixmap(rect, *s_background);
    }
    m_background = addPixmap(background);

    auto timer = new QTimer(this);
    timer->setInterval(1000 / 30); // 30 fps
    timer->setSingleShot(false);
    connect(timer, &QTimer::timeout, this, &GameScene::update);
    timer->start();
}

void GameScene::update()
{
    auto pixmap = m_background->pixmap();
    {
        const auto bgHeight = s_background->height();
        QPainter painter(&pixmap);
        QRect rect(0, 0, painter.device()->width(), painter.device()->height());
        m_backgroundOffset = (m_backgroundOffset + 1) % bgHeight;
        QPoint offset(0, bgHeight - m_backgroundOffset);
        painter.drawTiledPixmap(rect, *s_background, offset);
    }
    m_background->setPixmap(pixmap);
}
