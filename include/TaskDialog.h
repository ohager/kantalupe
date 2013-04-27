#ifndef __TaskDialog_H
#define __TaskDialog_H

#include <QDialog>
#include "Task.h"

namespace k{ // moc need direct declaration

/**
The Task dialog offers a selection of possible Tasks.
@author O. Haeger
*/
	class TaskDialog : public QDialog
	{
		Q_OBJECT
	signals:
		void triggered(Task *);
	public:
		TaskDialog(const QString & wintitle, QWidget * p);
		~TaskDialog();
		/**

		  */
		Task * execute();

		// overload action stuff, for dynamic ui control
		void addAction(QAction *action);
		void addActions(const QList<QAction *> actions);
		void insertAction(QAction *before, QAction *action);
		void removeAction(QAction *action);
	protected slots:
		void onClickedTask(Task * t);

	private:
		int exec(); // hidden
		void setupUi();

		Task * mClickedTask;
		bool mActionsChanged;

	};


} // eons



#endif // __TaskDialog_H

