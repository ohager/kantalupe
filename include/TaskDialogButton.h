#ifndef __TaskSelectorButton_H
#define __TaskSelectorButton_H

#include <QToolButton>

namespace k{

class Task;

/**
A specialized button for the TaskDialog.
It visually represents a Task.
@author O. Haeger
*/
	class TaskDialogButton : public QToolButton
    {
	Q_OBJECT
	signals:
		void clicked(Task *);
    public:
		TaskDialogButton(Task * t,
                           QWidget * p=0);
		inline Task * task() const { return mTask; }
	private slots:
		void onClick();

    private:
		Task * mTask;

    };

} // eons


#endif // __TaskSelectorButton_H
