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
    QGraphicsPixmapItem *m_background = nullptr;
    quint8 m_backgroundOffset;
};

#endif // GAMESCENE_H
