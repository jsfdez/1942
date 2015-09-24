#include "pixmapcache.h"

#include <QString>
#include <QPixmap>
#include <QPainter>
#include <QPixmapCache>

QPixmap PixmapCache::character(const QChar &character)
{
    auto p = pixmap(QStringLiteral(":/asset/font.png"));
    return p.copy(character.cell() % 16 * 64, character.cell() / 16 * 64, 64,
        64);
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

QPixmap PixmapCache::explosion()
{
    return pixmap(QStringLiteral(":/asset/explosion.png"));
}

QPixmap PixmapCache::pauseText()
{
    QPixmap pixmap;
    const QString text = "PAUSE";
    if (!QPixmapCache::find(text, &pixmap))
    {
        pixmap = QPixmap(text.size() * 64, 64);
        pixmap.fill(Qt::transparent);
        {
            QPainter painter(&pixmap);
            for(int i = 0; i < text.size(); ++i)
            {
                painter.drawPixmap(i * 64, 0, 64, 64, character(text.at(i)));
            }
        }
        QPixmapCache::insert(text, pixmap);
    }
    return pixmap;
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
