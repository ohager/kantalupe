#include "DragStoppedEvent.h"


START_NS

DragStoppedEvent::DragStoppedEvent()
	: QEvent(global::DragStopped)
{}


DragStoppedEvent::~DragStoppedEvent()
{
}


END_NS


