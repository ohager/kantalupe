#include "TaskDialogButton.h"
#include "Task.h"
#include "global.h"



START_NS

TaskDialogButton::TaskDialogButton(Task * t, QWidget * p)
			: QToolButton(p), mTask(t)
{

	setIcon(t->icon());
	setToolTip(t->toolTip());
	setText( t->text() );

	setAutoRaise(true);
	setIconSize( QSize(128,128) );
	setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	connect(this, SIGNAL(clicked()), this, SLOT(onClick()));
}


void TaskDialogButton::onClick()
{
	emit clicked(task());
}


END_NS


