#ifndef GRAPHICSPLAYERITEM_H
#define GRAPHICSPLAYERITEM_H

#include <QSet>
#include <QTimer>
#include <QVector2D>

#include "abstractgraphicsplaneobject.h"

class GraphicsPlayerObject : public AbstractGraphicsPlaneObject
{
    Q_OBJECT

public:
    GraphicsPlayerObject(QGraphicsItem *parent = nullptr);

    virtual int type() const override;

protected:
    virtual QVector2D direction() const override;
    virtual QPixmap pixmap() const;
    virtual void move() override;
    virtual void trigger() override;

private:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    QSet<std::underlying_type<Qt::Key>::type> m_keys;
    QTimer m_triggerTimer;
};

#endif // GRAPHICSPLAYERITEM_H
