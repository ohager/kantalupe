#include "DragUtility.h"

#include <QApplication>
#include <QPoint>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMouseEvent>
#include <QMimeData>
#include <QWidget>


#include "global.h"
#include "Drag.h"

START_NS

QPoint DragUtility::sDragStartPosition;

DragUtility::DragUtility()
{
}


void DragUtility::announceDrag(QMouseEvent * event)
{
	if(event->buttons().testFlag(Qt::LeftButton))
	{
		sDragStartPosition = event->pos();
	}
}

bool DragUtility::confirmDrag(QMouseEvent * event)
{
	return event->buttons().testFlag(Qt::LeftButton) &&
			(event->pos() - sDragStartPosition).manhattanLength() >= QApplication::startDragDistance();
}

Qt::DropAction DragUtility::executeDrag(QWidget * dragSource, QMimeData * mimedata, Qt::DropActions actions)
{
	Drag * drag = new Drag(dragSource);
	drag->setMimeData(mimedata);
	return drag->exec( actions );
}



END_NS
