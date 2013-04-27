#ifndef SurveyEditorModelPage_H
#define SurveyEditorModelPage_H

#include "EditorBasePage.h"


namespace k{

	class SurveyModelViewer;
	class TreeItem;
	/**
	  The base Survey Editor page.
	  Subclassing is necessary.
	  @author O. Haeger
	  */
	class SurveyEditorModelPage : public EditorBasePage
	{
		Q_OBJECT
	public:
		SurveyEditorModelPage(QWidget * parent=0x0);
		~SurveyEditorModelPage();

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
	private:
		void setupUi();

		SurveyModelViewer * mSurveyModelViewer;
	};

} // eons
#endif // SurveyEditorBasePage_H
