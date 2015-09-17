#include "gamescene.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(0, 0, 600, 800, parent)
{
    QPixmap background(":/asset/sea.png");
    Q_ASSERT(!background.isNull());
    addPixmap(background);
}
