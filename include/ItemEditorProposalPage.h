#ifndef ITEMEDITORProposalPAGE_H
#define ITEMEDITORProposalPAGE_H

#include <QWidget>
#include <QModelIndex>

#include "EditorBasePage.h"


class QAbstractItemModel;
class QMimeData;
class QCheckBox;
class QTreeWidgetItem;


namespace k{

	class ProposalTreeWidget;
	class PlainTextEdit;
	class LineEdit;
	class ImageListWidget;

	/**
	  The Editor page for Proposal.
	  @author O. Haeger
	  */
	class ItemEditorProposalPage : public EditorBasePage
	{
	public:
		Q_OBJECT
	public:
		ItemEditorProposalPage(QWidget * parent=0x0);
		~ItemEditorProposalPage();

		bool isAcceptingMime(const QMimeData *m) const;
		void update(TreeItem * item);

	protected:
		void commit(TreeItem * item) const;
		void setupUi();

	protected slots:
		void onSelectedRow(int);
		void onProposalTextChanged();
		void onMultipleChoiceClicked(bool);
		void onDoubleClickedProposal(QModelIndex);
		//void onItemChanged(QTreeWidgetItem *, int);
		//void onProposalImageChanged();
		//void onSolutionCheckChanged(bool);
	private:
		//k::ImageListWidget * mImageListWidget;
		k::ProposalTreeWidget * mProposalOverview;
		k::PlainTextEdit * mProposalTextEdit;
		QCheckBox * mMultipleChoiceCheck;
		//QWidget * mEditPart;
	};

} // eons
#endif // ITEMEDITORProposalPAGE_H
