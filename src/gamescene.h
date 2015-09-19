#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

class GameScene : public QGraphicsScene
{
public:
    GameScene(QObject *parent = 0);

private slots:
    void update();

private:
//    QGraphicsPixmapItem *m_background = nullptr;
//    QGraphicsItem *m_background = nullptr;
    QGraphicsPixmapItem *m_player = nullptr;
    quint8 m_backgroundOffset = 0;
    quint8 m_playerFrame = 0;
};

#endif // GAMESCENE_H
