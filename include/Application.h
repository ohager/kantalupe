#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "global.h"



namespace k{



/**
  The kantalupe Application
  It supports some additional features, especially for k:Widget-subclasses

@par User Mode
  The application can switch between different user modes. This allows
  the to change the Ui at runtime, e.g. to differ between Novice Level Ui and
  Expert Level Ui. There are two ways to respond on user mode changes

-# listen for userModeChanged() signals for regular QObject/QWidget subclasses
  -# using k:Widget directly.

  The latter has a default behaviour coupled to the provided OptionFlags of k::Widget.
  It is implemented in k::Widget::userModeEvent() and can be overridden. So, k:Widget
  supports the user mode changes natively, which makes
  it quite comfortable to react @e consistently on user mode changes.
  The signal-concept for user mode changes allows the user to apply the trigger directly
  to existing QObjects, e.g. QLabel, without the need of k::Widget-subclassing.
  The disadvantage is, that the behaviour must be implemented each time in an appropriate slot
  and may differ from k::Widgets behaviour, which in turn can be considered as an advantage,
as it is slightly more flexible.
  */
class Application : public QApplication
{
	Q_OBJECT
signals:
	/**
	  Emitted whenever the applications' user mode changes.
	  @param newmode The new mode
	  @param oldmode The previous mode
	  */
	void userModeChanged(global::UserModeType newmode,
						 global::UserModeType oldmode);
public:


	Application(int & argc, char ** argv);

	/**
	  Changes the user mode and emits signal userModeChanged().
	  Additionally, the userModeEvent() for k::Widget is posted also.
	  @param um The new user mode
	  @see userMode();
	  */
	void setUserMode(global::UserModeType um );
	inline global::UserModeType userMode() const { return mCurrentUserMode; }



protected:
	//bool event(QEvent *);
	bool eventFilter(QObject *, QEvent *);

private:
	global::UserModeType mCurrentUserMode;
};

} // eons

#endif // APPLICATION_H
