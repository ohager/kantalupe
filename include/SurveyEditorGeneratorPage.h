#ifndef SurveyEditorGeneratorPage_H
#define SurveyEditorGeneratorPage_H

#include "EditorBasePage.h"
#include <QItemSelection>

class QToolBar;
class QStandardItem;
class QLabel;

namespace k{

class LineEdit;
class PlainTextEdit;
class GeneratorScriptView;
class ScriptEngine;
class SurveyTree;
class ScriptListLoaderThread;
	/**
	  The Survey Editor Generator page.
	@author O. Haeger
	  */
	class SurveyEditorGeneratorPage : public EditorBasePage
	{
		Q_OBJECT
	signals:
		void surveyGenerated(SurveyTree*);
	public:
		SurveyEditorGeneratorPage(QWidget * parent=0x0);
		~SurveyEditorGeneratorPage();

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
	public slots:
		/**
		  Updates the script list.
		  */
		void updateScriptList();

	protected:
		virtual void commit(TreeItem * item) const;
		void closeEvent(QCloseEvent *);
		void initScriptLoader();
		void stopScriptLoader();

	protected slots:
		void onScriptsLoaded();
		void onSelectedItem(QStandardItem * item);
		void runScript(const QString & program);
		void onActionRunScript();
	private:


		void setupUi();

		ScriptListLoaderThread * mScriptLoader;
		GeneratorScriptView * mScriptView;
		LineEdit * mAuthorEdit,
				* mVersionEdit;

		PlainTextEdit	* mDescriptionEdit;

		ScriptEngine * mScriptEngine;
		//QStandardItem * mSelectedItem;
	};

} // eons
#endif

