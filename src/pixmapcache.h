#ifndef PIXMAPCACHE_H
#define PIXMAPCACHE_H

class QChar;
class QPixmap;
class QString;

struct PixmapCache
{
    static QPixmap character(const QChar &character);
    static QPixmap background();
    static QPixmap sea();
    static QPixmap player();
	static QPixmap greenEnemy();
    static QPixmap whiteEnemy();
    static QPixmap bossEnemy();
    static QPixmap bullet();
    static QPixmap explosion();

    static QPixmap pauseText();

private:
    static QPixmap pixmap(const QString& path);
};

#endif // PIXMAPCACHE_H
