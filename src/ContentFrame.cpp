#include "ContentFrame.h"
#include "Application.h"
#include "Drag.h"

#include <QtGui>

START_NS

ContentFrame::ContentFrame(QWidget * parent)
	: Widget(parent, AlwaysVisible | ShowDropIndicator)
{
	setAcceptDrops(true);

}


ContentFrame::~ContentFrame()
{

}

QSize ContentFrame::sizeHint () const
{

	return size();
}

bool ContentFrame::isAcceptingMime(const QMimeData *m) const
{
	return m->formats().first() == "test";
}

void ContentFrame::mousePressEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton)
			mDragStartPos = e->pos();
}

void ContentFrame::mouseMoveEvent(QMouseEvent * e)
{

	if (!(e->buttons() & Qt::LeftButton))
			 return;
	 if ((e->pos() - mDragStartPos ).manhattanLength()
		  < Application::startDragDistance())
			return;

	 Drag *drag = new Drag(this);
	 QMimeData *mimeData = new QMimeData;

	 mimeData->setData("test", "Empty data");
	 drag->setMimeData(mimeData);

	 drag->exec(Qt::CopyAction);

}



END_NS


