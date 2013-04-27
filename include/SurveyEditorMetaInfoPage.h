#ifndef SurveyEditorMetaInfoPage_H
#define SurveyEditorMetaInfoPage_H

#include "EditorBasePage.h"
#include <QRegExpValidator>

namespace k{
	class LineEdit;
	class PlainTextEdit;


	/**
	  The Survey Editor Meta Information page.
	  @author O. Haeger
	  */
	class SurveyEditorMetaInfoPage: public EditorBasePage
	{
		Q_OBJECT
	public:
		SurveyEditorMetaInfoPage(QWidget * parent=0x0);
		~SurveyEditorMetaInfoPage();

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
		void onValidateEmail(const QString &);
	private:
		void setupUi();

		QString mEmailOverlayTextBuffer;
		LineEdit * mFirstNameEdit,
					* mLastNameEdit,
					* mEmailEdit,
					* mPhoneEdit;
		PlainTextEdit * mWelcomeTextEdit,
						* mRemindTextEdit,
						* mThankTextEdit;
	};

} // eons
#endif
