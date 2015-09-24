#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

class GraphicsPlayerObject;

class GameScene : public QGraphicsScene
{
public:
    enum
    {
        FPS = 30,

        PlayerType = Qt::UserRole + 1,
        EnemyType,
        BulletType,
        BackgroundType,
    };

    GameScene(QObject *parent = 0);

public slots:
	void spawnEnemies();
    void spawnPlayer();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private slots:
    void update();
    void planeShot(QVector<QPair<QPoint, QVector2D>> bullets);

private:
    GraphicsPlayerObject *m_player = nullptr;
    bool m_paused = false;
};

#endif // GAMESCENE_H
