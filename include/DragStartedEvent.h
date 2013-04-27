#ifndef DRAGSTARTEDEVENT_H
#define DRAGSTARTEDEVENT_H


#include <QEvent>
#include <QMimeData>

#include "global.h"

namespace k{

	/**
	  The event for recently started drag events
	  @see k::Widget and k::Drag for kantalupe's drag indication feature.
	  @author O. Haeger
	  */
	class DragStartedEvent : public QEvent
	{
	public:
		/**
		  @param dragsource The source object that started the drag execution.
		@param mime The mime data (reference) that is put into QDrag
		 */
		explicit DragStartedEvent(QWidget * dragsource,
								  const QMimeData * mime);
		~DragStartedEvent();
		inline QWidget * source() const { return _dragSrc; }
		inline const QMimeData * mimeData() const { return _mimeData; }
	private:
		QWidget * _dragSrc; // ref only
		const QMimeData * _mimeData;
	};

} // eons


#endif // DRAGSTARTEDEVENT_H
