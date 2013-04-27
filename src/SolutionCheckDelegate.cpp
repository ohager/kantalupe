#include "SolutionCheckDelegate.h"
#include "global.h"
#include <QtGui>

START_NS

SolutionCheckDelegate::SolutionCheckDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}


QWidget *SolutionCheckDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &/* option */,
	const QModelIndex &/* index */) const
{
	QCheckBox * editor = new QCheckBox();
	editor->setObjectName("solution_checkbox");
	editor->setTristate(false);
	editor->setChecked(false);
	return editor;
}

void SolutionCheckDelegate::setEditorData(QWidget *editor,
									const QModelIndex &index) const
{
	bool checked = index.model()->data(index, Qt::EditRole).toBool();

	QCheckBox * cb= static_cast<QCheckBox*>(editor);
	cb->setChecked(checked);

}

void SolutionCheckDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
								   const QModelIndex &index) const
{
	QCheckBox * cb  = static_cast<QCheckBox*>(editor);
	model->setData(index, QVariant(cb->isChecked()) , Qt::EditRole);
}

void SolutionCheckDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}

END_NS
