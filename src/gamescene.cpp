#include "gamescene.h"

#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>

#include "pixmapcache.h"
#include "graphicshudobject.h"
#include "customeasingcurve.h"
#include "graphicsbulletitem.h"
#include "graphicsenemyobject.h"
#include "graphicsplayerobject.h"
#include "graphicsbackgrounditem.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(0, 0, 600, 800, parent)
    , m_hudObject(new GraphicsHudObject(PLAYER_HEALTH))
{
    addItem(new GraphicsBackgroundItem);
    addItem(m_hudObject);

    connect(m_hudObject, &GraphicsHudObject::gameOver, this,
        &GameScene::showGameOverText);

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameScene::update);
    timer->start(1000 / FPS);

    spawnPlayer();
}

GameScene::~GameScene()
{
}

bool GameScene::isPaused() const
{
    return m_paused;
}

void GameScene::spawnEnemies(GraphicsEnemyObject::EnemyType type, bool inverted)
{
    QEasingCurve curve;

    switch (type)
    {
    case GraphicsEnemyObject::EnemyType::White:
    case GraphicsEnemyObject::EnemyType::Green:
        curve.setType(static_cast<QEasingCurve::Type>(qrand() % 41));
        break;
    case GraphicsEnemyObject::EnemyType::Boss:
        curve.setCustomType(&CustomEasingCurve::simpleEasingCurve);
        break;
    }

    auto enemy = new GraphicsEnemyObject(type, curve, inverted);
    addItem(enemy);
    connect(enemy, &GraphicsEnemyObject::cannonTriggered, this,
        &GameScene::planeShot);
    connect(enemy, &GraphicsEnemyObject::exploded, this,
        &GameScene::planeExploded);
}

void GameScene::spawnPlayer()
{
    Q_ASSERT(!m_player);

    addItem(m_player = new GraphicsPlayerObject(PLAYER_HEALTH));

    const auto playerSize = m_player->boundingRect().size();
    QPointF pos{
        sceneRect().width() / 2 - playerSize.width() / 2,
        sceneRect().height()/* - playerSize.height()*/,
    };
    m_player->setPos(pos);
    m_hudObject->setHealth(m_player->health());
    addItem(m_player);
    connect(m_player, &GraphicsPlayerObject::cannonTriggered, this,
        &GameScene::planeShot);
    connect(m_player, &GraphicsPlayerObject::exploded, this,
        &GameScene::planeExploded);
    connect(m_player, &GraphicsPlayerObject::damaged, m_hudObject,
        &GraphicsHudObject::addScore);
    connect(m_player, &GraphicsPlayerObject::damaged, m_hudObject,
        &GraphicsHudObject::setHealth);
    connect(m_player, &GraphicsPlayerObject::exploded, m_hudObject,
        &GraphicsHudObject::playerDeath);
    setFocusItem(m_player);
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_P:
        if(m_paused)
        {
            showPauseText(false);
            m_paused = false;
        }
        else
        {
            showPauseText(true);
            m_paused = true;
        }
        break;
    default:
        QGraphicsScene::keyPressEvent(event);
    }
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    if(m_gameOverItem)
        emit restart();
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
    if(player && !player->isInvencible())
    {
        Q_ASSERT(player == m_player);

        const auto playerRect = player->sceneBoundingRect();
        for(auto plane : planes)
        {
            if(plane != player)
            {
                const auto enemyRect = plane->sceneBoundingRect();
                if (playerRect.intersects(enemyRect))
                    player->impact(std::numeric_limits<qint32>::max());
            }
        }
    }

    for(auto item : items())
    {
        if(item->type() == BulletType || item->type() == EnemyBulletType)
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
                    auto plane = qgraphicsitem_cast<
                        AbstractGraphicsPlaneObject*>(*it);
                    const auto status = plane->status();
                    if(status == AbstractGraphicsPlaneObject::Status::Alive
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

    if(--m_spawnEnemiesTicks == 0) // Spawn enemies
    {
        if(!(qrand() % 24)) // 1/25
            spawnEnemies(GraphicsEnemyObject::EnemyType::Boss, true);
        else
            spawnEnemies(GraphicsEnemyObject::EnemyType::White, true);
        m_spawnEnemiesTicks = m_spawnEnemiesMaxTicks;
    }
    else if(m_spawnEnemiesTicks == m_spawnEnemiesMaxTicks / 2)
    {
        if(!(qrand() % 24)) // 1/25
            spawnEnemies(GraphicsEnemyObject::EnemyType::Boss, false);
        else
            spawnEnemies(GraphicsEnemyObject::EnemyType::Green, false);
    }

    if(m_respawnTicks && --m_respawnTicks == 0)
        spawnPlayer();

    QGraphicsScene::advance();
}

void GameScene::planeShot(QVector<QPair<QPoint, QVector2D>> bullets)
{
    for(auto& pair : bullets)
    {
        const auto s = static_cast<AbstractGraphicsPlaneObject*>(sender());
        auto bullet = new GraphicsBulletItem(pair.first, pair.second,
            s->type() == PlayerType);
        addItem(bullet);
    }
}

void GameScene::planeExploded()
{
    auto plane = static_cast<AbstractGraphicsPlaneObject*>(sender());
    if(plane->type() == PlayerType)
    {
        m_respawnTicks = 2 * FPS;
        m_player = nullptr;
    }
    else
    {
        auto enemy = qgraphicsitem_cast<GraphicsEnemyObject*>(plane);
        m_hudObject->addScore(enemy->enemyType()
            == GraphicsEnemyObject::EnemyType::Boss ? 1000 : 10);
    }
}

void GameScene::showPauseText(bool show)
{
    if(show)
    {
        m_pauseItem = addPixmap(PixmapCache::pauseText());
        const auto center = m_pauseItem->boundingRect().center();
        m_pauseItem->setPos(width() / 2 - center.x(),
            height() / 2 - center.y());
    }
    else
    {
        delete m_pauseItem;
        m_pauseItem = nullptr;
    }
}

void GameScene::showGameOverText(quint32 score)
{
    m_gameOverItem = addPixmap(PixmapCache::gameOverText());
    const auto center = m_gameOverItem->boundingRect().center();
    m_gameOverItem->setPos(width() / 2 - center.x(),
        height() / 2 - center.y());
    m_paused = true;
    emit gameFinished(score);
}
