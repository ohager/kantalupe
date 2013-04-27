#ifndef __DropZoneIndicator_H
#define __DropZoneIndicator_H

#include <QWidget>
//#include <QMimeData>

class QMimeData;
class DXDroppable;




/**
The drop zone marker widget. It is used by DXDroppable, so direct usage of this class is 
uncommon.
@author O. Haeger
*/
class DropZoneIndicator : public QWidget
{
	Q_OBJECT
signals:
	/**
	Emitted whenever the visibility has changed, by mark or unmark
	@param visible @e true if visible
	*/
	void visibilityChanged(bool visible);
public:
	/**
	@param d The droppable interface, that is associated to this marker.
	@param parent The parent widget
	*/
	DropZoneIndicator(DXDroppable * d, QWidget * parent=0x0);

public slots:
	/**
	Makes the drop marker visible, if @ mime is accepted
	@note uses the DXDroppable interface
	@param unmark()
	*/
	void mark(const QMimeData * mime);
	/**
	Hides this indicator, if was marked priorly, else does nothing.
	*/
	void unmark();
protected:
	void showEvent(QShowEvent*);
	void dragEnterEvent(QDragEnterEvent * e);
	void dragMoveEvent(QDragMoveEvent * e);
	void dropEvent(QDropEvent * e);

private:
	DXDroppable * mDroppable;

};

#endif // __DXDrag_H

