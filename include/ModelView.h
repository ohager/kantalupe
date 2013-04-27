#ifndef MODELVIEW_H
#define MODELVIEW_H
#include "ModelViewReadOnly.h"
#include "TreeItemProtocol.h"

namespace k{

/**
  The model view with model editing capabilities.
  @author Oliver Haeger
  */
class ModelView : public ModelViewReadOnly{

	Q_OBJECT
public:
	ModelView(QWidget * parent=0);
public slots:
	void saveAsModel();

	void addNewModel();
	void addNewCategory();
	void addNewGroup();
	void addNewMatrix();
	void addNewProblem();
	void addNewMatrixProblem();


protected:
	void contextMenuEvent( QContextMenuEvent * event );

protected slots:
	void onActionRemove();
	void onActionClear();

private:
	types::Actions getActionsByItemType(tip::ItemType type, QObject * parent) const;
	QModelIndex mClickedIndex;
};


} //eons

#endif // MODELVIEW_H
