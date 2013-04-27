#include "MessageHandler.h"
#include <QMutexLocker>

MessageHandler * MessageHandler::sInstance=0x0;
QMutex Mutex;

#define SYNC QMutexLocker l(&Mutex)

//----------------------------------- STATICS --------------------

MessageHandler * MessageHandler::instance()
{
	SYNC;
	if(!sInstance)
		sInstance = new MessageHandler();
	return sInstance;
}

void MessageHandler::debug(	const QString & classname, 
							const QString & func, 
							const QString & what)
{
#ifdef _DEBUG
	// prepare secure strings, else the references might be invalid under certain circumstances, e.g. closing application
	QString c(classname); c.detach();
	QString f(func); f.detach();
	QString m(what); m.detach();
	qDebug( "%s::%s:--%s",	c.toAscii().data(),
							f.toAscii().data(),
							m.toAscii().data());
#endif
}

void MessageHandler::message(const QString & title, const QString & msg, QMessageBox::Icon type)
{
	
	instance()->post(title, msg, type);
}


void MessageHandler::error(	const QString & classname, 
							const QString & func, 
							const QString & what,
							const QString & d)
{
	
	QString detail= QString(tr("In %1::%2 occurred an error:\n%3\n\n%4")
								.arg(classname).arg(func).arg(what).arg(d));
	instance()->post(tr("Error"),what, detail, QMessageBox::Critical);
}

void MessageHandler::warning(	const QString & classname, 
							const QString & func, 
							const QString & what,
							const QString & d)
{
	
	QString detail= QString(tr("In %1::%2 occurred a warning:\n%3\n\n%4")
								.arg(classname).arg(func).arg(what).arg(d));
	instance()->post(tr("Warning"), what, detail, QMessageBox::Warning);
}




void MessageHandler::destroy()
{
	SYNC;
	delete sInstance; sInstance=0x0;
}
	
//----------------------------------- END STATICS --------------------

int MessageHandler::post(const QString & title, const QString & msg, QMessageBox::Icon type)
{
	QMessageBox box(type, title, msg);
	box.addButton( tr("Ok"), QMessageBox::AcceptRole);
	if(type==QMessageBox::Question)
	{
		box.addButton( tr("Cancel"), QMessageBox::RejectRole);
	}

	emit messagePosted(msg,type);

	return box.exec();
}

	
int MessageHandler::post(const QString & title, const QString & brief, const QString & detail, QMessageBox::Icon type)
{
	QMessageBox box(type, title, brief);
	box.addButton( tr("Ok"), QMessageBox::AcceptRole);
	if(type==QMessageBox::Question)
	{
		box.addButton( tr("Cancel"), QMessageBox::RejectRole);
	}

	box.setDetailedText(detail);

	emit messagePosted(brief,type);
	return box.exec();
}


MessageHandler::MessageHandler()
{

}
	
MessageHandler::~MessageHandler()
{
}

