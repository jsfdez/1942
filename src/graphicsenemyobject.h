#pragma once

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

    virtual QRectF boundingRect() const;

protected:
    virtual QVector2D direction() const override;

private:
    virtual QPixmap pixmap() const override;

    std::function<QPixmap()> m_pixmap;
    QEasingCurve m_curve;
	qreal m_time = 0.0f;
	bool m_inverted = false;
};
