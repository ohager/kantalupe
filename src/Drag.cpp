#include "Drag.h"
#include "DragStartedEvent.h"
#include "DragStoppedEvent.h"
#include "Application.h"

START_NS

Drag::Drag ( QWidget * dragSource )
	: QDrag(dragSource) {}

Drag::~Drag()
{
	qDebug("killing drag..");
	Application::postEvent(kApp, new k::DragStoppedEvent()	);
}

Qt::DropAction Drag::exec ( Qt::DropActions supportedActions  )
{
	Application::postEvent(kApp, new k::DragStartedEvent
		(	QDrag::source(),QDrag::mimeData()	)
	);
	return QDrag::exec(supportedActions);
}

Qt::DropAction Drag::exec ( Qt::DropActions supportedActions, Qt::DropAction defaultDropAction )
{
	Application::postEvent(kApp, new k::DragStartedEvent
		(	QDrag::source(),QDrag::mimeData()	)
	);
	return QDrag::exec(supportedActions, defaultDropAction);
}


END_NS
