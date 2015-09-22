#include "gamescene.h"

#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsPixmapItem>

#include "pixmapcache.h"
#include "graphicsbulletitem.h"
#include "graphicsenemyobject.h"
#include "graphicsplayerobject.h"
#include "graphicsbackgrounditem.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(0, 0, 600, 800, parent)
    , m_player(new GraphicsPlayerObject)
{
    addItem(new GraphicsBackgroundItem);
    {
        const auto playerSize = m_player->boundingRect().size();
        QPointF pos{
            sceneRect().width() / 2 - playerSize.width() / 2,
            sceneRect().height() - playerSize.height(),
        };
        m_player->setPos(pos);
    }
    addItem(m_player);
    connect(m_player, &GraphicsPlayerObject::cannonTriggered, this,
        &GameScene::planeShot);

    setFocusItem(m_player);

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameScene::update);
	timer->start(1000 / 30);

	auto spawnEnemiesTyper = new QTimer(this);
	connect(spawnEnemiesTyper, &QTimer::timeout, this,
		&GameScene::spawnEnemies);
    spawnEnemiesTyper->start(2000);
}

void GameScene::spawnEnemies()
{
	auto type = static_cast<QEasingCurve::Type>(qrand() % 41);
	QEasingCurve curve(type);
	addItem(new GraphicsEnemyObject(GraphicsEnemyObject::EnemyType::Green,
        curve, true));
    auto deferredEnemy = new GraphicsEnemyObject(
        GraphicsEnemyObject::EnemyType::Green, curve, false);
    QTimer::singleShot(1000, std::bind(&GameScene::addItem, this,
        deferredEnemy));
}

void GameScene::update()
{
    Q_ASSERT(sender() == findChild<QTimer*>());

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

//        if(item->type() == PlayerType || item->type() == EnemyType)
//        {
//            planes.append(dynamic_cast<AbstractGraphicsPlaneObject*>(item));
//        }
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
