#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent)
: QGraphicsView(parent)
{
}

void GraphicsView::drawBackground(QPainter*, const QRectF&)
{
}

void GraphicsView::drawForeground(QPainter */*painter*/, const QRectF &/*rect*/)
{
}

