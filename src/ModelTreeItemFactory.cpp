#include "ModelTreeItemFactory.h"
#include "global.h"

START_NS




ModelTreeItemFactory::ModelTreeItemFactory(){

}

void ModelTreeItemFactory::applyStyle(TreeItem * item)
{
	tip::ItemType t = item->getItemType();

	QColor bg, fg;
	QFont font;
	Qt::Alignment alignment=0;
	if(t == tip::ItemModel)
	{
		bg = QColor(global::R.getValue("modelstyle/modelcolor_bg"));
		fg = QColor(global::R.getValue("modelstyle/modelcolor_fg"));

		fontStyle(global::R.getValue("modelstyle/modeltextstyle"),
				  global::R.getValue("modelstyle/modeltextsize"),
				  font
				  );

		alignment = align(global::R.getValue("modelstyle/modeltextalign"));
	}
	else if(t == tip::ItemCategory)
	{
		bg = QColor(global::R.getValue("modelstyle/categorycolor_bg"));
		fg = QColor(global::R.getValue("modelstyle/categorycolor_fg"));
		fontStyle(global::R.getValue("modelstyle/categorytextstyle"),
				  global::R.getValue("modelstyle/categorytextsize"),
				  font
				  );

		alignment = align(global::R.getValue("modelstyle/categorytextalign"));

	}
	else if(t == tip::ItemGroup)
	{
		bg = QColor(global::R.getValue("modelstyle/groupcolor_bg"));
		fg = QColor(global::R.getValue("modelstyle/groupcolor_fg"));
		fontStyle(global::R.getValue("modelstyle/grouptextstyle"),
				  global::R.getValue("modelstyle/grouptextsize"),
				  font
				  );

		alignment = align(global::R.getValue("modelstyle/grouptextalign"));
	}
	else if(t == tip::ItemMatrix)
	{
		bg = QColor(global::R.getValue("modelstyle/matrixcolor_bg"));
		fg = QColor(global::R.getValue("modelstyle/matrixcolor_fg"));
		fontStyle(global::R.getValue("modelstyle/matrixtextstyle"),
				  global::R.getValue("modelstyle/matrixtextsize"),
				  font
				  );
		alignment = align(global::R.getValue("modelstyle/matrixtextalign"));

	}
	else if(t == tip::ItemMatrixProblem )
	{
		bg = QColor(global::R.getValue("modelstyle/matrixproblemcolor_bg"));
		fg = QColor(global::R.getValue("modelstyle/matrixproblemcolor_fg"));
		fontStyle(global::R.getValue("modelstyle/matrixproblemtextstyle"),
				  global::R.getValue("modelstyle/matrixproblemtextsize"),
				  font
				  );

		alignment = align(global::R.getValue("modelstyle/matrixproblemtextalign"));
	}
	else if(t == tip::ItemProblem )
	{
		bg = QColor(global::R.getValue("modelstyle/problemcolor_bg"));
		fg = QColor(global::R.getValue("modelstyle/problemcolor_fg"));
		fontStyle(global::R.getValue("modelstyle/problemtextstyle"),
				  global::R.getValue("modelstyle/problemtextsize"),
				  font
				  );

		alignment = align(global::R.getValue("modelstyle/problemtextalign"));
	}
	else
	{
		return;
	}

	item->setBackground( QBrush( bg ) );
	item->setForeground( QBrush( fg ) );
	item->setFont( font );
	item->setTextAlignment( alignment );
}

void ModelTreeItemFactory::fontStyle(const QString & cstyle, const QString & size, QFont & f)
{
	QString style(cstyle.toLower());
	if(style!="normal")
	{
		f.setItalic( style.contains("italic") );
		f.setBold( style.contains("bold") );
	}

	f.setPointSize( size.toInt() );
}

Qt::Alignment ModelTreeItemFactory::align(const QString &ca)
{
	QString a(ca.toLower());
	if(a=="right")
		return Qt::AlignRight;
	else if(a=="center")
		return Qt::AlignCenter;

	return Qt::AlignLeft;

}

END_NS

