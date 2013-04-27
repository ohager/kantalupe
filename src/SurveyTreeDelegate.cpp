#include "SurveyTreeDelegate.h"
#include "global.h"

#include "SurveyTree.h"
#include "TreeItem.h"
#include "TreeView.h"
#include <QPainter>

START_NS


/**
  @todo Use AllowedTypeCombination instead of MarkMask
  */

SurveyTreeDelegate::SurveyTreeDelegate(QObject  * parent )
	: QStyledItemDelegate(parent)
{

	unmarkAllItemTypes();

}
#define OFFSET tip::ItemUnspecified
void SurveyTreeDelegate::markItemType(tip::ItemType type, bool marked)
{
	// this is fucking hardcoded!
	// ItemUnspecified is first item in enum determining the numeric begin, i.e. 200
	Q_ASSERT_X(type - OFFSET<10,"SurveyTreeDelegate::markItemType","Array too small");
	mMarkMask[type - OFFSET]=marked;

}

void SurveyTreeDelegate::unmarkAllItemTypes()
{
	memset(mMarkMask,false,sizeof(mMarkMask));
}

void SurveyTreeDelegate::paint( QPainter * painter,
							   const QStyleOptionViewItem & option,
							   const QModelIndex & index ) const
{

	QStyledItemDelegate::paint(painter, option, index);

	SurveyTree * stree = (SurveyTree *)index.model();
	TreeItem * item = stree->itemFromIndexAsTreeItem(index);


	if(TreeView::isItemCollapsed(index)) // collapse other than Problem-Items
	{
		const QString text("[...]");
		QFont f;
		f.setPixelSize(8);
		f.setItalic(true);

		painter->setFont( f );
		QRectF rect(option.rect);
		rect.adjust(0,0,-8,0);
		painter->drawText(rect, Qt::AlignRight | Qt::AlignVCenter, text );
	}

	if(mMarkMask[item->getItemType()-OFFSET])
	{
		static QColor Color(global::R.getValue("surveystyle/itemdropcolor"));
		Color.setAlpha(128);
		static QBrush Brush( Color ) ;

		painter->save();
		painter->fillRect(option.rect, Brush );
		painter->restore();
	}


}

END_NS
