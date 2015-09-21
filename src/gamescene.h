#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

class GraphicsPlayerObject;

class GameScene : public QGraphicsScene
{
public:
    enum
    {
        PlayerType = Qt::UserRole + 1,
        EnemyType,
        BulletType,
        BackgroundType,
    };

    GameScene(QObject *parent = 0);

private slots:
    void update();
    void planeShot(QVector<QPair<QPoint, QVector2D>> bullets);

private:
    GraphicsPlayerObject *m_player = nullptr;
};

#endif // GAMESCENE_H
