#ifndef ItemEditor_H
#define ItemEditor_H

#include <QWidget>
#include "WidgetExtension.h"

class QListWidget;
class QListWidgetItem;
class QStackedWidget;

namespace k{

class TreeItem;

class ItemEditor : public QWidget//, private k::WidgetExtension
{
	Q_OBJECT

public:

	ItemEditor(QWidget * parent=0x0);

public slots:
	void changePage(QListWidgetItem *current, QListWidgetItem *previous);

	/**
	  Calling this, will open the correct editor (pages) for passed item
	  @param item The item, which shall be edited
	  */
	void openEditor(TreeItem * item);
	void updateEditor(TreeItem * item);
	void commit();
	//void reset();
	void openEditorModel();
protected:
	//void openEditor(const Category & c);
	//void updateEditor(const Category & c);


	void openEditorCategory();
	void openEditorMatrix();
	void openEditorGroup();
	void openEditorProblem();
	void openEditorMatrixProblem();


protected:

	void setupUi();

private:

	void createItems();

	QListWidget *mContentsWidget;
	QStackedWidget *mPagesWidget;

	QListWidgetItem * mModelButton,
					* mCategoryButton,
					* mMatrixButton,
					* mMatrixProblemButton,
					* mGroupButton,
					* mProblemButton,
					* mProposalButton,
					* mPropertiesButton;

	int mPageModel,
		mPageProblem,
		mPageCategory,
		mPageMatrix,
		mPageMatrixProblem,
		mPageGroup,
		mPageProposal,
		mPageProperties;

};

} // eons

#endif // ItemEditor_H
