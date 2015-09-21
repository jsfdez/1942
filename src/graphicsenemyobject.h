#ifndef GRAPHICSENEMYOBJECT_H
#define GRAPHICSENEMYOBJECT_H

#include "graphicsplayerobject.h"

class GraphicsEnemyObject : public GraphicsPlayerObject
{
	Q_OBJECT

public:
	GraphicsEnemyObject(QGraphicsItem *parent = nullptr);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter,
		const QStyleOptionGraphicsItem* option, QWidget* widget);
	virtual void advance(int phase);

private:
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);
};

#endif // GRAPHICSENEMYOBJECT_H
