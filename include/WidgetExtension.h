#ifndef WidgetExtension_H
#define WidgetExtension_H


#include <QString>
#include <QPixmap>
#include <QObject>
//#include <QPointer>



class QMimeData;
class QWidget;
class QDropEvent;
class QMouseEvent;



namespace k{

class Overlay;
class UserModeEvent;
class DragStartedEvent;
class DragStoppedEvent;



/**
  The widget extension wrapper extends a widget by some additional functionality
  */
class WidgetExtension : public QObject
{
	Q_OBJECT

public:
	class Listener // QObject does not allow nested classes
	{
	public:
		virtual bool isAcceptingMime(WidgetExtension * wx, const QMimeData * d) const = 0;
		virtual void onUserModeChange(WidgetExtension * wx, UserModeEvent * e) = 0;
		virtual void onDragStarted(WidgetExtension * wx, DragStartedEvent * e) = 0;
		virtual void onDragStopped(WidgetExtension * wx, DragStoppedEvent * e) = 0;
		virtual void onDrop(WidgetExtension * wx, QDropEvent * e) = 0;
	};

	/**
	  The Kantalupe WidgetExtension supports special option flags.
	  */
	enum Option{
		NoOptions = 0x0, ///< No options at all
		VisibleInNoviceModeOnly = 0x1, ///< In novice mode this WidgetExtension is visible
		VisibleInExpertModeOnly = 0x2, ///< In expert mode this WidgetExtension is visible
		ShowDropIndicator = 0x4, ///< Shows a drop indicator when a drag event started application wide.
		AlwaysVisible  = VisibleInNoviceModeOnly | ///< Always visible, independent of mode
						 VisibleInExpertModeOnly,
		AllOptions = 0xFFFF

	};
	Q_DECLARE_FLAGS(Options, Option)
	Q_FLAGS(Options)

	explicit WidgetExtension(QWidget * widget,	Options opt= AlwaysVisible, QObject * parent = 0x0);
	virtual ~WidgetExtension();


	Options optionFlags() const { return mOptFlags; }
	void setOptionFlags(Options opts) { mOptFlags = opts; }
	void setOption(Option o, bool enable){	enable ?
											mOptFlags |=  o :
											mOptFlags &= ~o;}

	/**
	  Sets the callback listener
	  @param l The Listener object. If already added one, the old one is deallocated.
	  @note The WidgetExtension is initalized with a WXListenerDefault
	  */
	void setListener(Listener * l);

	/**
	  @return The widget that was passed on ctor.
	  */
	inline QWidget * widget() { return _widget; }

	/**
	  @return The overlay for the drag and drop indication.
	  A user might to customize the overlay.
	  @note The overlay is owned by the wrapped widget, that was passed on
		this extension's construction
	  @see WidgetExtension::ShowDropIndicator
	  */
	Overlay * dropIndicator();


protected:
	virtual bool eventFilter(QObject *, QEvent *);

private:

	Options mOptFlags;
	QWidget * _widget;
	WidgetExtension::Listener * mListener;
	Overlay * _dropIndicator;
};


// --------------------- Default Listener Implementation -----------------------------
class WxListenerDefault : public WidgetExtension::Listener
{
	public:
	bool isAcceptingMime(WidgetExtension * wx, const QMimeData * d) const;
	void onUserModeChange(WidgetExtension * wx, UserModeEvent * e);
	void onDragStarted(WidgetExtension * wx, DragStartedEvent * e);
	void onDragStopped(WidgetExtension * wx, DragStoppedEvent * e);
	void onDrop(WidgetExtension * wx, QDropEvent * e);
};

} // eons

Q_DECLARE_OPERATORS_FOR_FLAGS(k::WidgetExtension::Options)



#endif // WidgetExtension_H
