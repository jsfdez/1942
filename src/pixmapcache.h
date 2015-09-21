#ifndef PIXMAPCACHE_H
#define PIXMAPCACHE_H

class QPixmap;
class QString;

struct PixmapCache
{
    static QPixmap sea();
    static QPixmap player();
	static QPixmap greenEnemy();
    static QPixmap whiteEnemy();
    static QPixmap bossEnemy();
    static QPixmap bullet();

private:
    static QPixmap pixmap(const QString& path);
};

#endif // PIXMAPCACHE_H
