#ifndef DRAGSTOPPEDEVENT_H
#define DRAGSTOPPEDEVENT_H

class QWidget;
#include <QEvent>

#include "global.h"

namespace k{

	/**
	  The event for recently stopped drag events
	  @see k::WidgetExtension and k::Drag for kantalupe's drag indication feature.
	  @author O. Haeger
	  */
	class DragStoppedEvent : public QEvent
	{
	public:
		DragStoppedEvent();
		~DragStoppedEvent();
	private:
	};

} // eons


#endif // DRAGSTOPPEDEVENT_H
