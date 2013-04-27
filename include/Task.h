#ifndef TASK_H
#define TASK_H

#include <QAction>

namespace k{

class Task : public QAction
{
	Q_OBJECT
public:
	Task(QObject * parent=0x0);
	Task(const QIcon & icon,
		 const QString & text,
		 const QString & tooltip,
		 QObject * parent=0x0 );

};

} //eons

#endif // TASK_H
