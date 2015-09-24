#include "gamescene.h"

#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>

#include "pixmapcache.h"
#include "graphicshudobject.h"
#include "graphicsbulletitem.h"
#include "graphicsenemyobject.h"
#include "graphicsplayerobject.h"
#include "graphicsbackgrounditem.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(0, 0, 600, 800, parent)
    , m_player(new GraphicsPlayerObject)
    , m_hudObject(new GraphicsHudObject)
{
    addItem(new GraphicsBackgroundItem);
    addItem(m_hudObject);
    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameScene::update);
    timer->start(1000 / FPS);

    spawnPlayer();
}

void GameScene::spawnEnemies(GraphicsEnemyObject::EnemyType type, bool inverted)
{
    QEasingCurve::Type curveType;

    switch (type)
    {
    case GraphicsEnemyObject::EnemyType::White:
        curveType = static_cast<QEasingCurve::Type>(qrand() % 41);
        break;
    case GraphicsEnemyObject::EnemyType::Green:
        curveType = static_cast<QEasingCurve::Type>(qrand() % 41);
        break;
    case GraphicsEnemyObject::EnemyType::Boss:
        break;
    }

    QEasingCurve curve(curveType);
    auto enemy = new GraphicsEnemyObject(type, curve, inverted);
    addItem(enemy);
    connect(enemy, &GraphicsEnemyObject::cannonTriggered, this,
        &GameScene::planeShot);

}

void GameScene::spawnPlayer()
{
    if (m_player)
    {
        const auto playerSize = m_player->boundingRect().size();
        QPointF pos{
            sceneRect().width() / 2 - playerSize.width() / 2,
            sceneRect().height() - playerSize.height(),
        };
        m_player->setPos(pos);
        addItem(m_player);
        connect(m_player, &GraphicsPlayerObject::cannonTriggered, this,
                &GameScene::planeShot);
    }
    setFocusItem(m_player);
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_P:
        if(m_paused)
        {
            delete m_pauseItem;
            m_paused = false;
        }
        else
        {
            m_pauseItem = addPixmap(PixmapCache::pauseText());
            m_paused = true;
        }
        break;
    default:
        QGraphicsScene::keyPressEvent(event);
    }
}

void GameScene::update()
{
    Q_ASSERT(sender() == findChild<QTimer*>());

    if(m_paused) return;

    GraphicsPlayerObject* player = nullptr;
    QList<AbstractGraphicsPlaneObject*> planes;
    for(auto item : items()) // find planes
    {
        switch(item->type())
        {
        case PlayerType:
            player = qgraphicsitem_cast<GraphicsPlayerObject*>(item);
        case EnemyType:
            planes.append(dynamic_cast<AbstractGraphicsPlaneObject*>(item));
        }
    }
    if(player)
    {
        const auto playerRect = player->sceneBoundingRect();
        for(auto plane : planes)
            if(plane != player)
                if (playerRect.contains(plane->sceneBoundingRect()))
                    player->impact(std::numeric_limits<qint32>::max());
    }

    for(auto item : items())
    {
        if(item->type() == BulletType)
        {
            const auto rect = item->boundingRect().translated(item->pos());
            if(!sceneRect().contains(rect))
                delete item;
            else
            {
                bool impacted = false;
                for(auto it = planes.begin(); it != planes.end() && !impacted;
                    ++it)
                {
                    const auto planeRect = (*it)->sceneBoundingRect();
                    auto plane = qgraphicsitem_cast<GraphicsPlayerObject*>(*it);
                    if(plane->status() == GraphicsPlayerObject::Status::Alive
                       && planeRect.contains(rect))
                    {
                        plane->impact(100);
                        impacted = true;
                    }
                }
                if(impacted) delete item;
            }
        }
    }

    if(--m_spawnEnemiesTicks == 0)
    {
        spawnEnemies(GraphicsEnemyObject::EnemyType::White, true);
        m_spawnEnemiesTicks = m_spawnEnemiesMaxTicks;
    }
    else if(m_spawnEnemiesTicks == m_spawnEnemiesMaxTicks / 2)
        spawnEnemies(GraphicsEnemyObject::EnemyType::Green, false);

    QGraphicsScene::advance();
}

void GameScene::planeShot(QVector<QPair<QPoint, QVector2D>> bullets)
{
    for(auto& pair : bullets)
    {
        auto bullet = new GraphicsBulletItem(pair.first, pair.second);
        addItem(bullet);
    }
}
