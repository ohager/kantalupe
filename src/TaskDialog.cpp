#include "TaskDialog.h"

//#include "TabViewFactory.h"
#include "TaskDialogButton.h"
#include "global.h"

#include <QtGui>



#define CLASS "TaskDialog"

START_NS

		/*
class DialogParameter{
public:
	DialogParameter(global::TaskType t, const QString & i, const QString & tip)
		: Type(t), Icon(i), Tooltip(tip) {}

	global::TaskType Type;
	QIcon Icon;
	QString Tooltip;
};
*/


TaskDialog::TaskDialog(const QString & wintitle, QWidget * p)
	: QDialog(p, Qt::Tool | Qt::MSWindowsFixedSizeDialogHint ),
	mClickedTask(0x0),
	mActionsChanged(true)
{
	setWindowTitle(wintitle);
}

TaskDialog::~TaskDialog()
{
}

void TaskDialog::setupUi()
{
	setSizeGripEnabled(false);
	QVBoxLayout * mainlayout = new QVBoxLayout();
    mainlayout->setMargin(0);


    // creating the grid
    QGridLayout * glayout = new QGridLayout();
    glayout->setAlignment(Qt::AlignCenter);
    glayout->setMargin(0);


	QList<QAction *> alist = actions();
    const int LineBreakAt = 3;
    int row=0;
	int n= alist.size();
    for(int i=0; i<n; ++i)
    {
	    int col=i % LineBreakAt;
		QAction *  task = actions().at(i);
		TaskDialogButton * btn=new TaskDialogButton((Task*)task,this);
		connect(btn, SIGNAL(clicked(Task*)),this, SLOT(onClickedTask(Task*)) );
	    glayout->addWidget(btn, row, col);
	    if(col==0 && i!=0)
		    ++row;
    }

    mainlayout->addLayout(glayout);
    setLayout(mainlayout);
}

void TaskDialog::addActions(const QList<QAction *> actions)
{
	mActionsChanged = true;
	QDialog::addActions(actions);
}

void TaskDialog::addAction(QAction * a)
{
	mActionsChanged = true;
	QDialog::addAction(a);
}



void TaskDialog::insertAction(QAction *before, QAction *action)
{
	mActionsChanged = true;
	QDialog::insertAction(before, action);

}

void TaskDialog::removeAction(QAction *action)
{
	mActionsChanged = true;
	QDialog::removeAction(action);

}


void TaskDialog::onClickedTask(Task * t)
{
	qDebug("clicked task...");
	mClickedTask = t;
	mClickedTask->trigger();
	accept();
}


Task * TaskDialog::execute()
{
	if(mActionsChanged)
	{
		setupUi();
		mActionsChanged = false;
	}

	mClickedTask = 0x0;
	if(exec()== QDialog::Accepted )
	{
		return mClickedTask;
	}
	return 0x0;
}

int TaskDialog::exec()
{
	return QDialog::exec();
}

END_NS

