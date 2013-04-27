#ifndef ItemEditorGroupPage_H
#define ItemEditorGroupPage_H

#include "EditorBasePage.h"

namespace k{

	class PlainTextEdit;
	class LineEdit;

	/**
	  The Editor page for Group element.
	  @author O. Haeger
	  */
	class ItemEditorGroupPage : public EditorBasePage
	{
	public:
		Q_OBJECT
	public:
		ItemEditorGroupPage(QWidget * parent=0x0);
		~ItemEditorGroupPage();

		bool isAcceptingMime(const QMimeData *m) const;

		// interface implementation

		void update(TreeItem * item);

	protected:
		void commit(TreeItem * item) const;

	private:
		void setupUi();

	private:
		k::PlainTextEdit * mDescriptionTextEdit;
		k::LineEdit * mNameLineEdit;
	};

} // eons
#endif // ItemEditorGroupPage_H
