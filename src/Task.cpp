#include "Task.h"
#include "global.h"

START_NS

Task::Task(QObject * parent)
	: QAction(parent)
{
}

Task::Task(const QIcon & icon,
		   const QString & text,
		   const QString & tooltip,
		   QObject * parent)
	: QAction(icon,text, parent)
{
	setToolTip(tooltip);
}



END_NS
