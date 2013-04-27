#ifndef __Droppable_H
#define __Droppable_H

#include "DropZoneIndicator.h"


/**
Convenience Macro for declaring a widget using the Droppable interface drop-capable.
*/
#define MAKE_DROPPABLE private: void dropEventPrivate(QDropEvent * e){ dropEvent(e);	}

/**
An interface for using the drop zone marker.
With this interface one enables a sophisticated drag&drop indication feature 
helping the user where to drop draggable objects.

Usage: 
-# Implement isAcceptingMime with Drop-cabable widgets. Subclasses need to declare drop-capability using the MAKE_DROPPABLE macro.
-# Use dropZoneMarker() to mark an unmark, i.e. show and hide, the drop indicator.

@par Example
@code
class MyDroppableWidget : public QWidget, public Droppable
{
	Q_OBJECT
	MAKE_DROPPABLE
public:
	MyDroppableWidget(QWidget * parent) : QWidget(p), Droppable(this) { 	}
	
	// ... more

public slots:
	// quite useful to provide a tryDrop-Function.
	// if drop would be accepted it is indicated then.
	void tryDrop(const QMimeData * mime)
	{
		dropZoneMarker()->mark(mime);
	}

protected:
	bool isAcceptingMime(const QMimeData *mime)
	{
		return mime->hasFormat("MyMimeFormat");
	}
	

	void dropEvent(QDropEvent * e)
	{
		
		if(isAcceptingMime(e->mimeData()))
		{
			// do whatever is needed on drop
			// ...
		
			// typically a good idea to unmark on drop
			dropZoneMarker()->unmark();
			e->accept();
		}
		else{
			e->ignore();
		}
	}

};


// Exemplary usage of droppable widget in the main window (typical situation)
class MainWindow : public QMainWindow
{
public:
	  MainWindow(QWidget * p) 
		: QMainWindow(p)		
	  { 
		mMyDroppable = new MyDroppable(this);
		//... 
	  }
protected:
	// use dragEnterEvent for started drag
	void dragEnterEvent(QDragEnterEvent * e)
	{
		// if mMyDroppable accepts the mime data the marker is shown then.
		// u cann put many others here also. This results in a 
		// application wide dropping help. Whatever widget accepts whatever mime
		// it will indicate it.
		mMyDroppable->tryDrop(e->mimeData());
		//... use more Droppables here
	}

private:
	MyDroppableWidget * mMyDroppable;
};

@endcode

@todo Information hiding for dropZoneMarker(). 
Provide all necessary mark/unmark features in this interface.
@author O. Haeger
*/
class Droppable
{
friend class DropZoneIndicator;
public:

	/**
	@param holder Your subclassed widget instance, i.e. always 'this'
	*/
	Droppable(QWidget * holder)
	{
		mMarker = new DropZoneIndicator(this,holder);
	}
	
	inline DropZoneIndicator  * dropZoneMarker() {
		return mMarker; 
	}

protected:
	/**
	Checks whether the drop is accepted, or not. 
	@param [in] mime The mime data that will be inspected.
	*/
	virtual bool isAcceptingMime(const QMimeData *mime) = 0;

private:
        virtual void dropEventPrivate(QDropEvent * e) { Q_UNUSED(e); /* need to be overloaded see MAKE_DROPPABLE */}
private:
	DropZoneIndicator  * mMarker;
};


#endif 

