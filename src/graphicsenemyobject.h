#ifndef GRAPHICSENEMYOBJECT_H
#define GRAPHICSENEMYOBJECT_H

#include <functional>

#include <QEasingCurve>

#include "abstractgraphicsplaneobject.h"

class GraphicsEnemyObject : public AbstractGraphicsPlaneObject
{
	Q_OBJECT

public:
    enum class EnemyType : quint8
    {
        Green,
        White,
        Boss
    };

	GraphicsEnemyObject(EnemyType type, QEasingCurve easingCurve, bool inverted,
		QGraphicsItem *parent = nullptr);

    virtual void move() override;
    virtual int type() const override;

private:
    virtual QPixmap pixmap() const override;

    std::function<QPixmap()> m_pixmap;
    QEasingCurve m_curve;
	qreal m_time = 0.0f;
	bool m_inverted = false;
};

#endif // GRAPHICSENEMYOBJECT_H
