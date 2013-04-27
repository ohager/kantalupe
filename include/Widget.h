#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>

class QMimeData;


namespace k{


class UserModeEvent;
class DragStartedEvent;



/**
  The specialized Kantalupe widget.
  Additionally, to the QWidget features it supports an arbitrary event
  and Option flags.

  @par Drop Indicator
The widget supports a drop indication feature, i.e. when a drag event starts application wide,
this widget might indicate visually, that it accepts the recently dragged data.
To enable this feature, do the following:

-# Set the ShowDropIndicator option
-# Implement isAcceptingMime().
-# Instead of using QDrag::exec() use k::Drag::exec() when begin drag operation

@par Example
@code
class MyDroppableWidget : public k::Widget
{
	Q_OBJECT
public:
	MyDroppableWidget(QWidget * parent)
		: Widget(p) { 	}

	// ... more

protected:
	bool isAcceptingMime(const QMimeData *mime)
	{
		return mime->hasFormat("MyMimeFormat");
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
		k::Drag d;
	}

private:
	MyDroppableWidget * mMyDroppable;
};


  */
class Widget : public QWidget
{
    Q_OBJECT
public:
	/**
	  The Kantalupe widget supports special option flags.
	  */
	enum Option{
		NoOptions = 0x0, ///< No options at all
		VisibleInNoviceModeOnly = 0x1, ///< In novice mode this widget is visible
		VisibleInExpertModeOnly = 0x2, ///< In expert mode this widget is visible
		ShowDropIndicator = 0x4, ///< Shows a drop indicator when a drag event started application wide.
		AlwaysVisible  = VisibleInNoviceModeOnly | ///< Always visible, independent of mode
						 VisibleInExpertModeOnly,
		AllOptions = 0xFFFF

	};
	Q_DECLARE_FLAGS(Options, Option)
	Q_FLAGS(Options)

	explicit Widget(QWidget * parent = 0,
					Options opt= AlwaysVisible,
					Qt::WindowFlags f = 0);

	~Widget();


	Options optionFlags() const { return mOptFlags; }
	void setOptionFlags(Options opts) { mOptFlags = opts; }
	void setOption(Option o, bool enable){	enable ?
											mOptFlags |=  o :
											mOptFlags &= ~o;}


	/**
	  @param m The mime data
	  @return @e true, if the passed Mime data is accepted by this widget.
	  The default implementation always returns @e false.
	  @note Overload this method, if you want to make use of the Drop-Indicator feature
	  */
	virtual bool isAcceptingMime(const QMimeData * m) const;


	void setDropIndicatorPixmap(const QPixmap & p);
	void setDropIndicatorText(const QString & t);
	void setDropIndicatorFont(const QFont & f);
	const QPixmap * dropIndicatorPixmap() const;
	QString dropIndicatorText() const;
	const QFont & dropIndicatorFont() const;


protected:

	/**
	  Event when user mode was toggled
	  */
	virtual void userModeEvent(UserModeEvent *);
	/**
	  Event when any drag started (application wide)
	  */
	virtual void dragStartedEvent(DragStartedEvent *);

	void dropEvent(QDropEvent *);

	bool eventFilter(QObject *, QEvent *);




private:
	Options mOptFlags;
	QWidget * mDropIndicator;
};


} // eons

Q_DECLARE_OPERATORS_FOR_FLAGS(k::Widget::Options)


#endif // WIDGET_H
