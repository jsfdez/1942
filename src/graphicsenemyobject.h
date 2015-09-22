#ifndef GRAPHICSENEMYOBJECT_H
#define GRAPHICSENEMYOBJECT_H

#include <functional>

#include <QEasingCurve>

#include "graphicsplayerobject.h"

class GraphicsEnemyObject : public GraphicsPlayerObject
{
	Q_OBJECT

public:
    enum class EnemyType : quint8
    {
        Green,
        White,
        Boss
    };

	GraphicsEnemyObject(EnemyType type, QEasingCurve easingCurve,
		QGraphicsItem *parent = nullptr);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter,
		const QStyleOptionGraphicsItem* option, QWidget* widget);
	virtual void advance(int phase);
    virtual int type() const override;

private:
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);

    std::function<QPixmap()> m_pixmap;
	QEasingCurve m_easingCurve;
	qreal m_time = 0.0f;
};

#endif // GRAPHICSENEMYOBJECT_H
