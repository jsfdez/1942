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

    addItem(new GraphicsEnemyObject(GraphicsEnemyObject::EnemyType::Boss));

    setFocusItem(m_player);

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameScene::update);
    timer->start(1000 / 30);
}

void GameScene::update()
{
    Q_ASSERT(sender() == findChild<QTimer*>());

    QList<QGraphicsItem*> planes;
    for(auto item : items()) // find planes
        if(item->type() == PlayerType || item->type() == EnemyType)
            planes.append(item);

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
                    const auto planeRect = (*it)->boundingRect()
                            .translated((*it)->pos());
                    auto plane = qgraphicsitem_cast<GraphicsPlayerObject*>(*it);
                    if(plane->status() == GraphicsPlayerObject::Status::Alive
                       && planeRect.contains(rect))
                    {
                        plane->impact(100);
                        delete item;
                    }
                }
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
