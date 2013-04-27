#ifndef ITEMEDITORPropertiesPAGE_H
#define ITEMEDITORPropertiesPAGE_H

#include <QWidget>

#include "EditorBasePage.h"

class QAbstractItemModel;
class QMimeData;


namespace k{

	class PropertyEditWidget;
	class PlainTextEdit;
	class LineEdit;
	/**
	  The Editor page for Properties.
	  @author O. Haeger
	  */
	class ItemEditorPropertiesPage : public EditorBasePage
	{
	public:
		Q_OBJECT
	public:
		ItemEditorPropertiesPage(QWidget * parent=0x0);
		~ItemEditorPropertiesPage();

		bool isAcceptingMime(const QMimeData *m) const;
		void update(TreeItem * item);

	protected:
		void commit(TreeItem * item) const;

		void setupUi();

	private:
		PropertyEditWidget * mPropertyEditor;
	};

} // eons
#endif // ITEMEDITORPropertiesPAGE_H
