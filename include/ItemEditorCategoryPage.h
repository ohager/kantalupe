#ifndef ITEMEDITORCATEGORYPAGE_H
#define ITEMEDITORCATEGORYPAGE_H

#include "EditorBasePage.h"

namespace k{

class PlainTextEdit;
class LineEdit;

	/**
	  The Editor page for Category.
	  @author O. Haeger
	  */
	class ItemEditorCategoryPage : public EditorBasePage
	{
	public:
		Q_OBJECT
	public:
		ItemEditorCategoryPage(QWidget * parent=0x0);
		~ItemEditorCategoryPage();

		bool isAcceptingMime(const QMimeData *m) const;
		void update(TreeItem * item);

	protected:
		void commit(TreeItem * item) const;

	private:
		void setupUi();
		k::PlainTextEdit * mDescriptionTextEdit;
		k::LineEdit * mNameLineEdit;

	};

} // eons
#endif // ITEMEDITORCATEGORYPAGE_H
