#ifndef __MessageHandler_H
#define __MessageHandler_H

#include <QMessageBox>


/**
This class deals with messages, information, warnings, errors
to be bring up to GUI/User.
This class is Thread safe
*/
class MessageHandler : public QObject
{
	Q_OBJECT
signals:
	/**
	Emitted when a message was posted.
	@param msg the posted message
	*/
	void messagePosted(const QString & msg, QMessageBox::Icon type);
public:
	
        static MessageHandler * instance();

	/**
	Prints a message to console, iff in debug mode(_DEBUG must be defined)
	*/
	static void debug(	const QString & classname, 
						const QString & func, 
						const QString & what);

	static void message(const QString & title, const QString & msg, QMessageBox::Icon type);
	static void error(	const QString & classname, 
							const QString & func, 
							const QString & what,
							const QString & detail = QString());

	static void warning(	const QString & classname, 
							const QString & func, 
							const QString & what,
							const QString & detail = QString());


	virtual int post(const QString & title, const QString & brief, const QString & detail, QMessageBox::Icon type=QMessageBox::NoIcon);
	virtual int post(const QString & title, const QString & msg, QMessageBox::Icon type=QMessageBox::NoIcon);

public slots:
	static void destroy();
protected:
	MessageHandler();
	~MessageHandler();
private:
	static MessageHandler * sInstance;
};



#endif // __MessageHandler_H
