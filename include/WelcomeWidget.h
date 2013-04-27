#ifndef _WELCOMEWIDGET_H
#define _WELCOMEWIDGET_H

#include "Widget.h"

namespace k{
/**
  This welcome widget is shown as welcome screen in
  kantalupe Editor.
  @author O. Haeger
  */
class WelcomeWidget : public QWidget
{
	Q_OBJECT
public:
	WelcomeWidget(QWidget * parent = 0x0);
protected:
	void setupUi();

};


} // eons


#endif // WELCOMEWIDGET_H
