#include "DragStartedEvent.h"


START_NS

DragStartedEvent::DragStartedEvent(QWidget * ds,
								   const QMimeData * mime)
	: QEvent(global::DragStarted),
	_dragSrc(ds),
	_mimeData(mime)
{}


DragStartedEvent::~DragStartedEvent()
{
	_dragSrc = 0x0;
	_mimeData = 0x0;
}


END_NS

