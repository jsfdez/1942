#pragma once

#include <QTimer>
#include <QPointer>
#include <QGraphicsScene>

#include "defines.h"
#include "graphicsenemyobject.h"

class GraphicsHudObject;
class GraphicsPlayerObject;
class GraphicsGameOverItem;

class GameScene : public QGraphicsScene
{
public:
    enum
    {
        PlayerType = Qt::UserRole + 1,
        EnemyType,
        BulletType,
        EnemyBulletType,
        BackgroundType,
        PauseType,
    };

    GameScene(QObject *parent = 0);
    ~GameScene();

    bool isPaused() const;

public slots:
    void spawnEnemies(GraphicsEnemyObject::EnemyType type, bool inverted);
    void spawnPlayer();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private slots:
    void update();
    void planeShot(QVector<QPair<QPoint, QVector2D>> bullets);
    void planeExploded();

private:
    void showPauseText(bool show);
    void showGameOverText();

    GraphicsPlayerObject *m_player = nullptr;
    bool m_paused = false;
    quint32 m_spawnEnemiesMaxTicks = 2 * FPS;
    quint32 m_spawnEnemiesTicks = m_spawnEnemiesMaxTicks;
    quint32 m_respawnTicks = 0;
    GraphicsHudObject *m_hudObject = nullptr;
    QGraphicsItem* m_pauseItem;
    QGraphicsItem* m_gameOverItem;
};
