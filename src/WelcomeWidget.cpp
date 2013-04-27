#include "WelcomeWidget.h"

#include "global.h"
#include "AboutBox.h"
#include <QtGui>

START_NS

//------------------------ Private classes ---------------------





//--------------------------------------------------



WelcomeWidget::WelcomeWidget(QWidget * p)
	: QWidget(p)
{
	setupUi();

}



void WelcomeWidget::setupUi()
{
	QVBoxLayout * layout = new QVBoxLayout();

	// put more
	// idea: newsreader, most recent documents etc.

	layout->addWidget( new AboutBox() );
	setLayout(layout);

}




END_NS
