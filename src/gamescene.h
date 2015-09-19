#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

class GraphicsPlayerItem;

class GameScene : public QGraphicsScene
{
public:
    GameScene(QObject *parent = 0);

private slots:
    void update();

private:
    GraphicsPlayerItem *m_player = nullptr;
    int m_phase = -1;
};

#endif // GAMESCENE_H
