#ifndef SurveyEditorScriptPage_H
#define SurveyEditorScriptPage_H

#include "EditorBasePage.h"

class QTabWidget;
class QToolBar;
class QPlainTextEdit;

namespace k{

class SurveyTree;
class ScriptTextEdit;
class ScriptEngine;
class ScriptHighlighter;
class ScriptConsoleEdit;
class ScriptInfoWidget;

	/**
	  The Survey Editor Script page.
	  @author O. Haeger
	  */
	class SurveyEditorScriptPage: public EditorBasePage
	{
		Q_OBJECT
	signals:
		void surveyGenerated(SurveyTree *);
		void scriptDeployed(const QString & filename);
	public:
		SurveyEditorScriptPage(QWidget * parent=0x0);
		~SurveyEditorScriptPage();

		/**
		  @return @e true if a mime type is accepted, otherwise false.
		  Base implementation returns always false.
		  */
		virtual bool isAcceptingMime(const QMimeData *m) const;

		/**
		  Binds passed item as buddy to this page and updates this page with item'S data.
		  Subclasses need to override this method. Always make a super call to this class first.
		  @param item The model item
		  */
		virtual void update(TreeItem * item);
	protected:
		virtual void commit(TreeItem * item) const;
	protected slots:
		void onActionRunScript();
		void onActionLoadScript();
		void onActionSaveScript();
		void onActionDeployScript();
		void onEditedScript();
		void onActionNewScript();
	private:
		void setupUi();

		QToolBar * mToolBar;
		QAction * mActionDeploy;
		ScriptTextEdit * mScriptEdit;
		ScriptEngine * mScriptEngine;
		ScriptConsoleEdit * mScriptConsole;
		ScriptInfoWidget * mScriptInfoEdit;
		QTabWidget * mScriptEditTab;
		int mUsedApiLevel;
	};

} // eons
#endif // SurveyEditorBasePage_H
