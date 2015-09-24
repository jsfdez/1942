#include "pixmapcache.h"

#include <QString>
#include <QPixmap>
#include <QPainter>
#include <QPixmapCache>

#include "gamescene.h"

QPixmap PixmapCache::character(const QChar &character)
{
    auto p = pixmap(QStringLiteral(":/asset/font.png"));
    return p.copy(character.cell() % 16 * 64, character.cell() / 16 * 64, 64,
                  64);
}

QPixmap PixmapCache::hudNumber(quint32 number)
{
    const auto height = HUD_HEIGHT - 4;
    const auto numberPixmap = [height](const QChar &digit)
    {
        QPixmap pixmap;
        const auto name = QString("hudNumber_%1").arg(digit);
        if (!QPixmapCache::find(name, &pixmap))
        {
            pixmap = PixmapCache::character(digit).scaledToHeight(height);
            QPixmapCache::insert(name, pixmap);
        }
        return pixmap;
    };
    const auto numberCount = 5;
    QPixmap pixmap(height * numberCount, height);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    for(int i = 0; i < numberCount; ++i)
    {
        auto p = numberPixmap(QString("%1").arg(number % 10).at(0));
        painter.drawPixmap(pixmap.width() - (i + 1) * height, 4, p);
        number /= 10;
    }
    return pixmap;
}

QPixmap PixmapCache::background()
{
    return pixmap(QStringLiteral(":/asset/background.png"));
}

QPixmap PixmapCache::sea()
{
    return pixmap(QStringLiteral(":/asset/sea.png"));
}

QPixmap PixmapCache::player()
{
    return pixmap(QStringLiteral(":/asset/player.png"));
}

QPixmap PixmapCache::playerLife()
{
    const auto name = QStringLiteral("playerLife");
    QPixmap pixmap;
    if (!QPixmapCache::find(name, &pixmap))
    {
        pixmap = player().copy(0, 0, player().width() / 4,
            player().height()).scaledToHeight(HUD_HEIGHT - 4);
        QPixmapCache::insert(name, pixmap);
    }
    return pixmap;
}

QPixmap PixmapCache::greenEnemy()
{
    return pixmap(QStringLiteral(":/asset/enemy.png"));
}

QPixmap PixmapCache::whiteEnemy()
{
    return pixmap(QStringLiteral(":/asset/shooting-enemy.png"));
}

QPixmap PixmapCache::bossEnemy()
{
    return pixmap(QStringLiteral(":/asset/boss.png"));
}

QPixmap PixmapCache::bullet()
{
    return pixmap(QStringLiteral(":/asset/bullet.png"));
}

QPixmap PixmapCache::enemyBullet()
{
    return pixmap(QStringLiteral(":/asset/enemy-bullet.png"));
}

QPixmap PixmapCache::explosion()
{
    return pixmap(QStringLiteral(":/asset/explosion.png"));
}

QPixmap PixmapCache::text(const QString &string)
{
    QPixmap pixmap;
    if (!QPixmapCache::find(string, &pixmap))
    {
        pixmap = QPixmap(string.size() * 64, 64);
        pixmap.fill(Qt::transparent);
        {
            QPainter painter(&pixmap);
            for(int i = 0; i < string.size(); ++i)
            {
                painter.drawPixmap(i * 64, 0, 64, 64, character(string.at(i)));
            }
        }
        QPixmapCache::insert(string, pixmap);
    }
    return pixmap;
}

QPixmap PixmapCache::pauseText()
{
    return text(QStringLiteral("PAUSE"));
}

QPixmap PixmapCache::gameOverText()
{
    return text(QStringLiteral("GAME OVER"));
}

QPixmap PixmapCache::pixmap(const QString &path)
{
    QPixmap pixmap;
    if (!QPixmapCache::find(path, &pixmap))
    {
        auto loaded = pixmap.load(path);
        if(!loaded) qFatal("Failed to load %s", path);
        else QPixmapCache::insert(path, pixmap);
    }
    return pixmap;
}
