#ifndef ITEMEDITORQUESTIONPAGE_H
#define ITEMEDITORQUESTIONPAGE_H

#include <QWidget>
#include "EditorBasePage.h"

class QCheckBox;
class QMimeData;

namespace k{

	class LineEdit;
	class ImageListWidget;
	class PlainTextEdit;

	/**
	  The Problem editor for items.
	  */
	class ItemEditorProblemPage : public EditorBasePage
	{
		Q_OBJECT
	public:
		ItemEditorProblemPage(QWidget * parent=0x0);
		~ItemEditorProblemPage();

		bool isAcceptingMime(const QMimeData *m) const;
		void update(TreeItem * item);

	protected:
		void commit(TreeItem * item) const;
		void setupUi();
		bool isUidAutoGeneration() const;
	private slots:
		void onQuestionTextChanged();
	private:
		k::PlainTextEdit * mQuestionTextEdit,
						* mHintTextEdit;
		k::LineEdit * mUidTextEdit;
		k::ImageListWidget * mImageList;

	};


} // eons


#endif // ITEMEDITORQUESTIONPAGE_H
