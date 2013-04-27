#ifndef ITEMEDITORMATRIXPROBLEMPAGE_H
#define ITEMEDITORMATRIXPROBLEMPAGE_H

#include <QWidget>
#include "EditorBasePage.h"

class QCheckBox;
class QMimeData;

namespace k{

	class LineEdit;
	class ImageListWidget;
	class PlainTextEdit;

	/**
	  The Question editor for items.
	  */
	class ItemEditorMatrixProblemPage : public EditorBasePage
	{
		Q_OBJECT
	public:
		ItemEditorMatrixProblemPage(QWidget * parent=0x0);
		~ItemEditorMatrixProblemPage();

		bool isAcceptingMime(const QMimeData *m) const;
		void update(TreeItem * item);

	protected:
		bool isUidAutoGeneration() const;
		void commit(TreeItem * item) const;
		void setupUi();

	private slots:
		//void onUidGenerationToggled(bool);
		void onQuestionTextChanged();
	private:

		k::LineEdit * mUidLineEdit;
		k::PlainTextEdit * mQuestionTextEdit;


	};


} // eons


#endif // ITEMEDITORMATRIXPROBLEMPAGE_H
