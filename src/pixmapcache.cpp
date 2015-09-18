#include "pixmapcache.h"

#include <QString>
#include <QPixmap>
#include <QPixmapCache>

const auto k_seaAsset = QStringLiteral(":/asset/sea.png");
const auto k_playerAsset = QStringLiteral(":/asset/player.png");

QPixmap PixmapCache::sea()
{
    return pixmap(k_seaAsset);
}

QPixmap PixmapCache::player()
{
    return pixmap(k_playerAsset);
}

QPixmap PixmapCache::pixmap(const QString &path)
{
    QPixmap pixmap;
    if (!QPixmapCache::find(path, &pixmap))
    {
        auto loaded = pixmap.load(path);
        if(!loaded)
            qFatal("Failed to load %s", path);
        else
            QPixmapCache::insert(path, pixmap);
    }
    return pixmap;
}
