#ifndef DRAGUTILITY_H
#define DRAGUTILITY_H

#include <Qt>

class QPoint;
class QDropEvent;
class QDragEnterEvent;
class QMouseEvent;
class QMimeData;
class QWidget;

namespace k{
/**
  A static class supporting/facilitating and unifying drag operations for
  drag sources.
  A drag process starts with an announcement, which is the initial event that @e could cause a drag operation.
  This is usually a left mouse button hold followed by a mouse movement.
  After announcement the drag operation may be confirmed, if e.g. the mouse move with hold button exceeds a
  predefined distance. Finally, iff confirmed the drag can be executed.
	Note, that DragUtility only supports the drag source side.  Accepting the dragged mime data and dropping
	cannot be generalized at all. It remains to user to implement the target's drop operation. Usually,
	you check the Mime type's acceptance on QWidget::dragEnterEvent(QDragEnterEvent*) and finalizes the drop
	on QWidget::dropEvent(QDropEvent*)

	@par Code Example
  @code
  void SourceWidget::mousePressEvent(QMouseEvent * event)
  {
	DragUtility::announceDrag(event);
	// ... your further implementation
  }

  void SourceWidget::mouseMoveEvent(QMouseEvent * event)
  {
	if(DragUtility::confirmDrag(event))
	{
		QByteArray data;
		// prepare your data array
		QMimeData * data = new QMimeData();
		data->setData(MyMimeType, data);
		DragUtility::executeDrag(this, mimedata, Qt::CopyAction | Qt::MoveAction);
	}
  }

  // ------- Target Widget's implementation -----

  void TargetWidget::dragEnterEvent(QDragEnterEvent * e)
  {
		if(e->mimeData()->hasFormat(MyMimeType) &&
			e->dropAction() == Qt::CopyAction) // target accepts only copy action
		{
			e->acceptProposedAction(); // causes to trigger drop then
		}
  }

  void TargetWidget::dropEvent(QDropEvent * e)
	{
		QByteArray data = e->mimeData(MyMimeType);
		// .. decode the carried data
		// do your stuff with this widget
		e->acceptProposedAction();
	}
  @endcode


  @author O. Haeger
  */
class DragUtility
{
public:
	/**
	  Announces a drag operation. Use this function in your source widget's mousePressEvent()
	  */
	static void announceDrag(QMouseEvent * event);

	/**
	  Confirms a drag operation. That is, if the conditions (user interaction) are met to potentially execute a
	  drag operation. Use this function in your source widget's mouseMoveEvent()
	  */
	static bool confirmDrag(QMouseEvent * event);

	/**
	  Executes the drag operation. Use this function in your source widget's mouseMoveEvent(), after an announced
	  drag was confirmed positively.
	  */
	static Qt::DropAction executeDrag(QWidget * dragsource, QMimeData * mimedata, Qt::DropActions actions);

private:
    DragUtility();
	static QPoint sDragStartPosition;
};

}

#endif // DRAGUTILITY_H
