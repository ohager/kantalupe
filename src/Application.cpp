#include "Application.h"
#include "UserModeEvent.h"
#include "PluginPool.h"

#include "global.h"

START_NS

Application::Application(int & argc, char ** argv)
	: QApplication(argc, argv), mCurrentUserMode()
{
	setApplicationVersion( global::Version );
	setOrganizationName("Clayhouse");
	setOrganizationDomain("clayhouse.de");
	setApplicationName("kantalupe-edit");

	setUserMode(global::UserModeNovice);



}



void Application::setUserMode(global::UserModeType um )
{
	global::UserModeType old = mCurrentUserMode;
	mCurrentUserMode = um;

	postEvent(this, new UserModeEvent(mCurrentUserMode, old)	);
	emit userModeChanged(mCurrentUserMode, old);
}


bool Application::eventFilter(QObject * o, QEvent * e)
{
	if(e->type()==QEvent::MouseMove)
		qDebug(".");

	return QApplication::eventFilter(o,e);
}


END_NS

