#ifndef PROPOSALTREEWIDGET_H
#define PROPOSALTREEWIDGET_H

#include <QTreeWidget>
#include <QObject>
#include "global.h"
#include "ProtocolTypes.h"

namespace k{

class Overlay;

/**
  The proposal tree widget. Note, that the solutions are provided also. This is for
  a better user experience. Internally, both data are handled separately.
  @author O. Haeger
 */
class ProposalTreeWidget : public QTreeWidget
{
	Q_OBJECT
signals:
	/**
	  Emitted whenever a row is selected.
	  @param r The selected row
	  */
	void rowSelected(int r);

	/**
	  Emitted whenever a proposal solution checkbox toggled
	  @param r The row of item
	  @param checked @e true if item is checked as solution
	  */
	//void solutionCheckToggled(int r, bool checked);
public:
	static const int InvalidItemId = -1;
	static const int ColumnId = 0; ///< The column index for Id
	static const int ColumnProposalText = 1;///< The column index for the text
	static const int ColumnSolutionCheck = 2; ///< The column index for check box
	static const int ColumnImageFile = 1; ///< The column index for Image file role (currently backpacked as data on proposal text)

	ProposalTreeWidget(QWidget * parent=0x0);

	/**
	  Adds proposal item at end of list.
	  @param proposal The proposal data
	  @param solution  @e true, oif this proposal is considered to be a solution
	  @note The id of @e proposal object is ignored, as adding will renumber items, i.e. change id
	  */
	void addProposalItem(const Proposal &proposal, bool solution);

	inline Overlay * overlay() { return mOverlay; }

	// the getter and setter for the tree's items

	types::Proposals getProposals() const;
	types::Solutions getSolutions() const;

	/**
	  Sets selection mode for solutions. Multiple selection means, that one or many items can be selected,
	  otherwise only one item can be selected exclusively.
	  @param multiple If @e true, multiple items can be selected. Default is true.
	  @see isSolutionSelectionMultiple()
	  */
	inline void setSolutionSelectionMultiple(bool multiple) { mSolutionSelectionMultiple = multiple; }
	inline bool isSolutionSelectionMultiple() const { return mSolutionSelectionMultiple; }

	/**
	  Dis-/Enables ability to add and remove new items.
	  @param enabled If @e true, add and remove operation is available for Ui (i.e. context menu)
	  Programatically, add/remove is still available.
	  */
	inline void setAddRemoveEnabled(bool enabled) { mAddRemoveEnabled=enabled; }
	inline bool isAddRemoveEnabled() const { return mAddRemoveEnabled; }

	/**
	  @return The aggregated proposal data structure for given row
	  */
	Proposal getProposalData(int row) const;

	/**
	  Checks whether this proposal is solution, or not.
	  @return @e true, if proposal is solution, otherwise false.
	  */
	bool isProposalSolution(const Proposal & p) const;

	/**
	  */
	void setProposalItemText(int row, const QString & text);




	/**
	  @return selected row, if nothing is selected -1 is returned.
	  */
	int selectedRow() const;


public slots:
	/**
	  Adds a new item at end of list
	  */
	void newProposalItem();

	/**
	  Renumbers the added items, i.e. assign possibly mixed
	  item set correct numbering order from 1 to @e n
	  */
	void renumber();

	/**
	  Sets all solutions to state 'false'
	  */
	void clearSolutionSelection();


protected:
	static const int ImageFileRole = Qt::UserRole; ///< Internal role used for setting ImageFile data on tree items
	static const int SolutionCheckRole = Qt::UserRole + 1; ///< Internal data role used for marking a proposal as solution, or not.

	/**
	  @return The item's check state. If row is invalid also false is returned;
	  @see setItemSolution();
	  */
	bool itemIsSolution(QTreeWidgetItem * item) const;
	void setItemSolution(QTreeWidgetItem * item, bool solution);

	void contextMenuEvent(QContextMenuEvent *);
	void showEvent(QShowEvent *);
	void resizeEvent(QResizeEvent *);
	void moveEvent(QMoveEvent *);


protected slots:

	void onClicked(QTreeWidgetItem*,int);
	void onActionClear();
	void onActionRemove();
	void onSelectionChange();
	void onItemChange(QTreeWidgetItem*,int);
private:
	//void incept(const types::ProposalData & src,QTreeWidgetItem * dest) const;
	//void extract(const QTreeWidgetItem * src, types::ProposalData & dest) const;
	QModelIndex indexFromRow(int r) const;
	QTreeWidgetItem * itemFromRow(int r) const;

	QModelIndex mClickedIndex;
	Overlay * mOverlay;
	bool mAddRemoveEnabled, mSolutionSelectionMultiple;
};

} // eons

#endif // PROPOSALTREEWIDGET_H
