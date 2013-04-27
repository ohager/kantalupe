#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "global.h"

class QSplitter;


namespace Ui {
    class MainWindow;
}

namespace k{

//class DockWidget;
class ContentFrame;
class ModalLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	/**
	  Predefined Layout types
	  @see changeLayout()
	  */
	enum LayoutType{
		SingleScreen = 200, ///< A single screen, No right content available
		SplitScreenHorizontal, ///< Two-columns arranged horizontally
		SplitScreenVertical ///< Two-columns arranged vertically
	};

	explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	/**
	  @return the 'right' content widget, if exists, otherwise null.
		Its existance depends on the LayoutType. This is the content widget
	  intenionally used for read-only interactions. Although it's named 'right'
	  content widget, its placement is not meant with it. It is leant on the 'rvalue'
	  naming in C++ Programming.
	  @see mainContentFrame();
	  */
	QWidget * rightContentWidget() const;


	/**
	  @return the main content widget. This is the content widget,
	  intentionally used for read/write interactions. This is also
	  the main interaction frame.
	  @see mainContentFrame();
	  */
	QWidget * mainContentWidget() const;

public slots:
	void showWelcomeScreen();
	void clearMainContent();
	void clearRightContent();

protected slots:


	void setup();

	void execTaskDialogNewTask();
	void execTaskDialogExport();
	void execTaskDialogExtras();

	void onTaskNewSurvey();
	void onTaskNewProject();
	void onTaskNewModel();
	void onTaskExportModel();
	void onTaskExportSurvey();
	void onTaskAbout();

	/**
	  Current implementation toggles between global::UserModeNovice and global::UserModeExpert
	  This method calls setUserMode() and changes the appearance of the associated button.
	  */
	void toggleUserMode();

	/**
	  Changes the main window's layout to a predefined type.
	  Changing the layout does not remove/deallocates the contents of holder widgets.
	  @param ltype The layout type
	  */
	void changeLayout(MainWindow::LayoutType ltype);

protected:
	void resizeEvent(QShowEvent * );
	void showEvent(QShowEvent*);
	void dragEnterEvent(QDragEnterEvent *);
	void dragMoveEvent(QDragMoveEvent *);
	void timerEvent(QTimerEvent *);
private:
	static const char * PropertyUserMode;
	void setupUi();
	/**
	  Confirms a running drag operation.
	  @note As there are (at least on Windows) problems detecting a mouse button release on external drag operations.
	  This workaround uses a timer to detect whether a drag operation is still in progress or not.
	  */
	void confirmDragOperation();


	int mTimerDragOperation;

    Ui::MainWindow *ui;
	QSplitter * mSplitter;
	QAction * mActionNewTask,
			* mActionNewExport,
			* mActionExtras,
			* mActionToggleUserMode;
	ModalLabel * mModalLabel;
};

} // eons

#endif // MAINWINDOW_H
