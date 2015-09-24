#pragma once

#include <QTimer>
#include <QGraphicsScene>

#include "graphicsenemyobject.h"

class GraphicsHudObject;
class GraphicsPlayerObject;

class GameScene : public QGraphicsScene
{
public:
    enum
    {
        FPS = 30,
        HudHeight = 50,

        PlayerType = Qt::UserRole + 1,
        EnemyType,
        BulletType,
        BackgroundType,
        PauseType,
    };

    GameScene(QObject *parent = 0);

public slots:
    void spawnEnemies(GraphicsEnemyObject::EnemyType type, bool inverted);
    void spawnPlayer();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private slots:
    void update();
    void planeShot(QVector<QPair<QPoint, QVector2D>> bullets);

private:
    GraphicsPlayerObject *m_player = nullptr;
    bool m_paused = false;
    quint32 m_spawnEnemiesMaxTicks = 2 * FPS;
    quint32 m_spawnEnemiesTicks = m_spawnEnemiesMaxTicks;
    QGraphicsItem *m_pauseItem = nullptr;
    GraphicsHudObject *m_hudObject;
};
