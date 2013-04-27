#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "Application.h"
#include "TaskDialog.h"
#include "Task.h"
#include "AboutBox.h"
#include "UserModeEvent.h"
#include "DragStartedEvent.h"
#include "DragStoppedEvent.h"

#include "Widget.h"

#include "WelcomeWidget.h"
#include "ItemEditor.h"

#include "ModelEditor.h"
#include "ModelTree.h"
//#include "ModelView.h"


#include "SurveyDataEditor.h"
#include "SurveyEditor.h"
#include "SurveyTree.h"

#include "SurveyExporter.h"
#include "SurveyExportSelector.h"

#include "Drag.h"
#include "ShortMessage.h"
#include "ModalLabel.h"

#include "global.h"


#include <QtGui>

START_NS


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mSplitter(0x0),
	mTimerDragOperation(0)
{
	setupUi();
	QTimer::singleShot(0, this, SLOT(setup()));

}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::setupUi()
{

	ui->setupUi(this);

	setAcceptDrops(true);

	// actions
	mActionNewTask = ui->mainToolBar->addAction(
				QIcon(global::R.getValue("icon","newtask")),
				tr("New task"),
				this,
				SLOT(execTaskDialogNewTask())
			);

	mActionNewExport = ui->mainToolBar->addAction(
				QIcon(global::R.getValue("icon","exporttask")),
				tr("Export"),
				this,
				SLOT(execTaskDialogExport())
			);

	mActionExtras = ui->mainToolBar->addAction(
				QIcon(global::R.getValue("icon","extrastask")),
				tr("Extras"),
				this,
				SLOT(execTaskDialogExtras())
			);


	ui->mainToolBar->addSeparator();
	mActionToggleUserMode = ui->mainToolBar->addAction(
				QString(),
				this,
				SLOT(toggleUserMode())
			);

	QFont font;
	font.setPointSize(14);
	font.setBold(true);
	mModalLabel = new ModalLabel(this);
	mModalLabel->setFont(font);
	mModalLabel->setPosition(ModalLabel::BottomRight);
	mModalLabel->setForegroundColor(QColor(128,128,128,80));
	mModalLabel->setBackgroundColor(Qt::transparent);
	mModalLabel->hide();


	menuBar()->hide();
}

void MainWindow::setup()
{
	setWindowState(Qt::WindowMaximized);
	// initialize user mode
	// calling toggleMode is to dispatch event AND update the action button's appearance
	kApp->setUserMode(global::UserModeNovice);
	toggleUserMode(); // will switch to Novice mode
	showWelcomeScreen();

}


QWidget * MainWindow::rightContentWidget() const
{
	if(mSplitter)
		return mSplitter->widget(0);
	else
	{
		qDebug("MainWindow: No right content widget available");
		return 0x0;
	}
}

QWidget * MainWindow::mainContentWidget() const
{
	if(mSplitter)
		return mSplitter->widget(1);
	else
		return centralWidget();


}

// ----------------------- EVENTS -----------------------------

void MainWindow::resizeEvent(QShowEvent * )
{
	// as modal label is NOT added to any layout, we need to trigger
	// resize events manually.
	mModalLabel->setPosition( mModalLabel->position() );
}


void MainWindow::showEvent(QShowEvent * )
{

}


void MainWindow::dragEnterEvent(QDragEnterEvent * x)
{
	// internal drags are posted using k::Drag
	// but external drags need to be posted explicitely
	if(!x->source()) // external drag has no source!
	{
		qDebug("external drag enter");
		x->accept();
		kApp->postEvent(kApp, new DragStartedEvent(this, x->mimeData()) );

	}
}

void MainWindow::dragMoveEvent(QDragMoveEvent * e)
{
	confirmDragOperation();
	e->accept();
}

void MainWindow::timerEvent(QTimerEvent * t)
{
	if(t->timerId() == mTimerDragOperation)
	{
		//drag stopped
		kApp->postEvent(kApp, new DragStoppedEvent());
		killTimer(mTimerDragOperation);
	}
}

void MainWindow::confirmDragOperation()
{
	if(mTimerDragOperation)
	{
		killTimer(mTimerDragOperation);
	}
	mTimerDragOperation = startTimer(1000);
}

// --------------------- SLOTS -----------------------------
void MainWindow::showWelcomeScreen()
{
	changeLayout(MainWindow::SingleScreen);

	QLayout * l = new QVBoxLayout();
	l->addWidget( new WelcomeWidget(this) );
	mainContentWidget()->setLayout( l );
	mModalLabel->setText(tr("Welcome to kantalupe"));
	mModalLabel->show();


}


void MainWindow::clearMainContent()
{
	mainContentWidget()->layout()->deleteLater();
}

void MainWindow::clearRightContent()
{
	rightContentWidget()->layout()->deleteLater();
}

void MainWindow::changeLayout(MainWindow::LayoutType l)
{

	if(mSplitter)
	{
		mSplitter->deleteLater();
		mSplitter = 0x0;
	}

	if(centralWidget())
	{
		centralWidget()->deleteLater();
	}

	if(l == MainWindow::SingleScreen)
	{
		setCentralWidget( new QWidget() );

	}
	else if( l == MainWindow::SplitScreenHorizontal )
	{
		mSplitter  = new QSplitter(Qt::Horizontal);
		mSplitter->setHandleWidth(1);
		mSplitter->addWidget( new QWidget() );
		mSplitter->addWidget( new QWidget() );
		setCentralWidget(mSplitter);
	}
	else if( l == MainWindow::SplitScreenVertical )
	{
		mSplitter  = new QSplitter(Qt::Vertical);
		mSplitter->setHandleWidth(1);
		mSplitter->addWidget( new QWidget() );
		mSplitter->addWidget( new QWidget() );
		setCentralWidget(mSplitter);
	}


}

void MainWindow::toggleUserMode()
{
	static const QString NoviceMode = tr("Novice Mode"),
				ExpertMode = tr("Expert Mode");


	// current implementation toggles between novice<->expert
	if(kApp->userMode() == global::UserModeNovice )
	{
		mActionToggleUserMode->setIcon(
			QIcon( global::R.getValue( "icon","expertmode" ) )
		);
		mActionToggleUserMode->setText( ExpertMode );
		mActionToggleUserMode->setToolTip(
			tr( "You are working in %1. Click to change to %2" )
				.arg(ExpertMode).arg( NoviceMode )
		);

		// new mode
		kApp->setUserMode( global::UserModeExpert );

	}
	else if(kApp->userMode() == global::UserModeExpert )
	{
		mActionToggleUserMode->setIcon(
			QIcon( global::R.getValue( "icon","easymode" ) )
		);
		mActionToggleUserMode->setText( NoviceMode );
		mActionToggleUserMode->setToolTip(
			tr( "You are working in %1. Click to change to %2" )
				.arg(NoviceMode).arg( ExpertMode )
		);

		// new mode
		kApp->setUserMode( global::UserModeNovice );
	}
	else
	{
		qDebug("Unknown mode '%u'", kApp->userMode());
	}

	ShortMessage::showMessage(this, tr("%1 mode activated").arg(kApp->userMode()==global::UserModeExpert?"Expert":"Novice"));
}

#define TICON(prefix,alias) QIcon(global::R.getValue(prefix, alias))
#define TCONNECT(t,m) connect(t,SIGNAL(triggered()),this, SLOT(m));
void MainWindow::execTaskDialogNewTask()
{

	// setup dialog
	TaskDialog * d= new TaskDialog(tr("Select New Task"),this);


	int optin = kApp->userMode() == global::UserModeNovice ? 1 : 2;

	QList<QAction*> tasks;

	if(optin <= 2)
	{
		QAction * newproject = new Task(
					TICON("task","newproject"),
					tr("New Project"),
					tr("Creates a new empty project"), d
				);
		TCONNECT(newproject,onTaskNewProject());

		QAction * newsurvey = new Task(
					TICON("task","newsurvey"),
					tr("New Survey"),
					tr("Creates a new empty survey based on a chosen model"), d
				);
		TCONNECT(newsurvey,onTaskNewSurvey());

		tasks << newproject << newsurvey;
	}


	if(optin == 2 )
	{
		QAction * newmodel = new Task(
					TICON("task","newmodel"),
					tr("New Model"),
					tr("Creates a new empty model"), d
				);
		TCONNECT(newmodel,onTaskNewModel());

		tasks << newmodel;
	}

	d->addActions( tasks );
	d->execute();

}

void MainWindow::execTaskDialogExtras()
{

	// setup dialog
	TaskDialog * d= new TaskDialog(tr("Select Extra"),this);


	int optin = kApp->userMode() == global::UserModeNovice ? 1 : 2;

	QList<QAction*> tasks;

	if(optin <= 2)
	{
		QAction * about = new Task(
					TICON("image","logo"),
					tr("About"),
					tr("Shows some information about this application"), d
				);
		TCONNECT(about,onTaskAbout());

		tasks << about;
	}


	if(optin == 2 )
	{
		// nothing yet
	}

	d->addActions( tasks );
	d->execute();

}

void MainWindow::execTaskDialogExport()
{
	TaskDialog * d= new TaskDialog(tr("Select Export Source"),this);

	int optin = kApp->userMode() == global::UserModeNovice ? 1 : 2;

	QList<QAction*> tasks;

	if(optin <= 2)
	{
		QAction * exportsurvey = new Task(
					TICON("task","exportsurvey"),
					tr("Export Survey"),
					tr("Exports a survey to other format"), d
				);
		TCONNECT(exportsurvey,onTaskExportSurvey());

		tasks << exportsurvey;
	}
	else if(optin == 2)
	{
		QAction * exportmodel = new Task(
					TICON("task","exportmodel"),
					tr("Export Model"),
					tr("Exports a model to other format"), d
				);
		TCONNECT(exportmodel,onTaskExportModel());

		tasks << exportmodel;
	}
	//else


	d->addActions( tasks );
	d->execute();
}


// ------------------------ TASKS ---------------------------

void MainWindow::onTaskNewSurvey()
{
	changeLayout(MainWindow::SplitScreenHorizontal);


	SurveyDataEditor * surveydataeditor = new SurveyDataEditor();

	///< @todo create a widget joining model and view! -->see ModelEditor
	SurveyEditor * surveyeditor = new SurveyEditor();

	connect(surveyeditor, SIGNAL(selectedItem(TreeItem*)), surveydataeditor, SLOT(openEditor(TreeItem*)));
	connect(surveydataeditor, SIGNAL(surveyGenerated(SurveyTree*)), surveyeditor, SLOT(setSurveyTree(SurveyTree*)));

	QWidget * editorwidget= rightContentWidget();
	editorwidget->setLayout( new QVBoxLayout() );
	editorwidget->layout()->addWidget( surveyeditor );

	QWidget * editor = mainContentWidget();

	QVBoxLayout * editlayout = new QVBoxLayout();
	editlayout->setMargin(0);
	editlayout->addWidget( surveydataeditor );
	editor->setLayout(editlayout);
	mModalLabel->setText(tr("Survey Editor"));
	mModalLabel->show();


	surveydataeditor->openEditor( surveyeditor->surveyTree()->rootItem() );

	//ShortMessage::showMessage(this, tr("Survey Editor"));
	//QTimer::singleShot(100, modelview , SLOT(loadModel()));

}

void MainWindow::onTaskNewProject()
{
	ShortMessage::showMessage(this, tr("Sorry, not implemented yet"));
	qDebug("todo: New Project");
}

void MainWindow::onTaskNewModel()
{

	changeLayout(MainWindow::SplitScreenHorizontal);

	ItemEditor * itemeditor = new ItemEditor();
	ModelEditor * modeleditor = new ModelEditor();
	connect(modeleditor, SIGNAL(selectedItem(TreeItem*)), itemeditor, SLOT(openEditor(TreeItem*)));


	QWidget * editorwidget= rightContentWidget();
	editorwidget->setLayout( new QVBoxLayout() );
	editorwidget->layout()->addWidget( modeleditor );

	QWidget * editor = mainContentWidget();

	QVBoxLayout * editlayout = new QVBoxLayout();
	editlayout->setMargin(0);
	editlayout->addWidget( itemeditor );
	editor->setLayout(editlayout);

	mModalLabel->setText(tr("Model Editor"));
	mModalLabel->show();

	itemeditor->openEditor( modeleditor->modelTree()->rootItem() );

}

void MainWindow::onTaskExportModel()
{
	ShortMessage::showMessage(this, tr("Sorry, not implemented yet"));
	qDebug("todo: Export as Model");
}

void MainWindow::onTaskExportSurvey()
{
	changeLayout(MainWindow::SplitScreenHorizontal);

	SurveyExporter * exporter = new SurveyExporter(new SurveyExportSelector());

	QWidget * editorwidget= mainContentWidget();
	editorwidget->setLayout( new QVBoxLayout() );
	editorwidget->layout()->addWidget( exporter->exportSelector() );

	QWidget * wexporter = rightContentWidget();
	wexporter->setLayout( new QVBoxLayout() );
	wexporter->layout()->addWidget( exporter );

	mModalLabel->setText(tr("Survey Export"));
	mModalLabel->show();
}


void MainWindow::onTaskAbout()
{
	//changeLayout(MainWindow::SingleScreen);
	QWidget * about = new AboutBox(this);
	about->setWindowFlags(Qt::Tool);
	about->show();
}


END_NS


