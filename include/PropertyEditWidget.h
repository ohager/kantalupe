#ifndef PROPERTYEDITWIDGET_H
#define PROPERTYEDITWIDGET_H

#include <QTreeWidget>
#include "ProtocolTypes.h"

class QModelIndex;

namespace k{

	class Overlay;

	/**
  Specialized QTreeWidget for multi-column property editing.
  @author O. Haeger
  */
	class PropertyEditWidget : public QTreeWidget
	{
		Q_OBJECT
	public:
		PropertyEditWidget(QWidget * parent);
		inline Overlay * overlay() { return mOverlay; }

		void addProperty(const Property & p);
		types::Properties getProperties() const;
	protected:
		void contextMenuEvent(QContextMenuEvent * e);
		void showEvent(QShowEvent *);
		void resizeEvent(QResizeEvent *);
		void moveEvent(QMoveEvent *);
	protected slots:
		void onActionAddProperty();
		void onActionEditProperty();
		void onActionRemoveProperty();
		void onActionClear();

	private:
		enum { Key=0, Value, Description };
		static QTreeWidgetItem * createItem(const Property & p);

		void setupUi();

		QModelIndex mClickedIndex;
		Overlay * mOverlay;
	};

} // eons

#endif // PROPERTYEDITWIDGET_H
