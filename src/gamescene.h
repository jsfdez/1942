#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

class GraphicsPlayerObject;

class GameScene : public QGraphicsScene
{
public:
    GameScene(QObject *parent = 0);

private slots:
    void update();
    void planeShot(QVector<QPair<QPoint, QVector2D>> bullets);

private:
    GraphicsPlayerObject *m_player = nullptr;
    int m_phase = -1;
};

#endif // GAMESCENE_H
