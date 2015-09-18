#ifndef PIXMAPCACHE_H
#define PIXMAPCACHE_H

class QPixmap;
class QString;

struct PixmapCache
{
    static QPixmap sea();
    static QPixmap player();

private:
    static QPixmap pixmap(const QString& path);
};

#endif // PIXMAPCACHE_H
