#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>
#include <QPointer>
//#include <QFrame>



namespace k{

class ContentFrame;

	/**
	A special featureless dock widget that is intended to be used as a
	tiled, (programatically) resizable area within a QMainWindow.
	Instead of setting a QWidget directly it uses setContent()
	for convenience.

	@author O. Haeger
	  */
class DockWidget : public QDockWidget
{
    Q_OBJECT
public:
	/**
	  Creates a dock widget with an already existing ContentFrame.
	  */
	explicit DockWidget(QWidget *parent = 0);

public:
	/**
	  Sets the width of the dock area's top-level content widget.
	  @param w The width,i.e the content's width, so the DockWidget might be
	  larger. When using width()
		@see contentWidth()
	  */
	void setContentWidth(int w);
	int contentWidth() const;

	/**
	  Sets the content for this dockwidget..
	  @param c The content frame. If already set, the previous one will be deleted and replaced.
	  @see content()
	  */
	void setContent(ContentFrame * c);
	ContentFrame * content() const;


protected:
	// protected, as content frame must not be overwritten
	void setWidget(QWidget *);


};


} // eons

#endif // DOCKWIDGET_H
