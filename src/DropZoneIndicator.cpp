#include "DropZoneIndicator.h"
#include "DXDroppable.h"

#include <QMimeData>
#include <QtGui>






DropZoneIndicator::DropZoneIndicator(DXDroppable * d, QWidget * parent)
:	QWidget(parent), mDroppable(d)
{
	QLayout * layout = new QVBoxLayout();
	QLabel * icon = new QLabel();
	icon->setPixmap( 
                        QPixmap(":icons/Resources/green_arrow_down.png")
			.scaledToWidth(24 , Qt::SmoothTransformation)
	);
	icon->setAttribute(Qt::WA_TranslucentBackground, true);
	icon->setAlignment( Qt::AlignHCenter );
	/*
	QLabel * label = new QLabel( "Drop Here" );
	label->setAttribute(Qt::WA_TranslucentBackground, true);
	QFont f;
	f.setPixelSize(10);
	label->setFont( f );
	label->setAlignment( Qt::AlignCenter );
	layout->addWidget(label);
	*/
	layout->addWidget( icon );
	layout->setSpacing(0);
	setLayout(layout);
	adjustSize();
	setVisible(false);
	setAcceptDrops(true);
}

void DropZoneIndicator::mark(const QMimeData * mime)
{
	if(mDroppable->isAcceptingMime(mime) && !isVisible())
	{
		// it seems that on external drag events (at least on Win32) do not trigger signal
		// destroyed(), dont know what to do!?
		connect(mime, SIGNAL(destroyed()), this, SLOT(unmark()) );
		show();
		emit visibilityChanged(true);
	}
}

void DropZoneIndicator::unmark()
{
	hide();
	emit visibilityChanged(false);
}

void DropZoneIndicator::showEvent(QShowEvent * e)
{
	Q_UNUSED(e);
	QWidget * p =(QWidget*)parent();

	int x=(p->width()/2) - (width()/2);
	int y=(p->height()/2) - (height()/2);

	move( x,y );

	//move( x,y );
}


void DropZoneIndicator::dragEnterEvent(QDragEnterEvent * e)
{
	e->acceptProposedAction();
}

void DropZoneIndicator::dragMoveEvent(QDragMoveEvent * e)
{
	e->acceptProposedAction();
}


void DropZoneIndicator::dropEvent(QDropEvent * e)
{
	mDroppable->dropEventPrivate(e); // delegate
}


