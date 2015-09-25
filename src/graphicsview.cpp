#include "graphicsview.h"

#include <QDebug>
#include <QBitmap>
#include <QResizeEvent>
#include <QApplication>

#include "gamescene.h"
#include "pixmapcache.h"

GraphicsView::GraphicsView(QWidget *parent)
: QGraphicsView(parent)
{
}

void GraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawBackground(painter, rect);
}

void GraphicsView::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawForeground(painter, rect);
	if(qApp->property("useOpenGL").toBool())
	{
		if(m_background.isNull())
		{
			QPixmap mask(rect.size().toSize());
			mask.fill(Qt::black);
			{
				QPainter painter(&mask);
				painter.fillRect(-rect.x(), -rect.y(), sceneRect().width(),
				sceneRect().height(), Qt::white);
			}
			auto pixmap = PixmapCache::background().scaled(rect.size().toSize());
			pixmap.setMask(mask.createMaskFromColor(Qt::black, Qt::MaskOutColor));
			m_background = pixmap;
		}
		painter->drawPixmap(rect, m_background, m_background.rect());
	}
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
    if(event->oldSize() != event->size())
    {
        m_background = QPixmap();
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
}
