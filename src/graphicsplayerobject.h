#pragma once

#include <QSet>
#include <QTimer>
#include <QVector2D>

#include "abstractgraphicsplaneobject.h"

class GraphicsPlayerObject : public AbstractGraphicsPlaneObject
{
    Q_OBJECT

public:
    GraphicsPlayerObject(const quint32 health, QGraphicsItem *parent = nullptr);

    virtual int type() const override;

signals:
    void focusLost();
    void focusReceived();

protected:
    virtual QVector2D direction() const override;
    virtual QPixmap pixmap() const;
    virtual void move() override;
    virtual void trigger() override;

private:
    virtual void focusInEvent(QFocusEvent* event);
    virtual void focusOutEvent(QFocusEvent* event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    QSet<std::underlying_type<Qt::Key>::type> m_keys;
    qint32 m_triggerPendingTicks;
    const qint32 k_triggerTicks;
};
