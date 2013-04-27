#ifndef SOLUTIONCHECKDELEGATE_H
#define SOLUTIONCHECKDELEGATE_H

#include <QItemDelegate>

namespace k{


	/**
	  A customized delegate for checkable solution widget inside ProposalTreeWidget
	  @author O. Haeger
	  */
class SolutionCheckDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit SolutionCheckDelegate(QObject *parent = 0);


	void setIconSize(const QSize & s) { mIconSize= s; }
	inline const QSize& iconSize() const { return mIconSize; }


	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
						  const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
					  const QModelIndex &index) const;

	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
	QSize mIconSize;

};

} // eons

#endif // SOLUTIONCHECKDELEGATE_H
