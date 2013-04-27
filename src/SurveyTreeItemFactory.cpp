#include "SurveyTreeItemFactory.h"
#include "global.h"

START_NS


SurveyTreeItemFactory::SurveyTreeItemFactory()
{

}


void SurveyTreeItemFactory::applyStyle(TreeItem * item)
{
	tip::ItemType t = item->getItemType();

	QColor bg, fg;
	QFont font;
	Qt::Alignment alignment=0;
	if(t == tip::ItemSurvey)
	{
		bg = QColor(global::R.getValue("surveystyle/surveycolor_bg"));
		fg = QColor(global::R.getValue("surveystyle/surveycolor_fg"));

		fontStyle(global::R.getValue("surveystyle/surveytextstyle"),
				  global::R.getValue("surveystyle/surveytextsize"),
				  font
				  );

		alignment = align(global::R.getValue("surveystyle/surveytextalign"));
	}
	else if(t == tip::ItemCategory)
	{
		bg = QColor(global::R.getValue("surveystyle/categorycolor_bg"));
		fg = QColor(global::R.getValue("surveystyle/categorycolor_fg"));
		fontStyle(global::R.getValue("surveystyle/categorytextstyle"),
				  global::R.getValue("surveystyle/categorytextsize"),
				  font
				  );

		alignment = align(global::R.getValue("surveystyle/categorytextalign"));

	}
	else if(t == tip::ItemGroup)
	{
		bg = QColor(global::R.getValue("surveystyle/groupcolor_bg"));
		fg = QColor(global::R.getValue("surveystyle/groupcolor_fg"));
		fontStyle(global::R.getValue("surveystyle/grouptextstyle"),
				  global::R.getValue("surveystyle/grouptextsize"),
				  font
				  );

		alignment = align(global::R.getValue("surveystyle/grouptextalign"));
	}
	else if(t == tip::ItemMatrix)
	{
		bg = QColor(global::R.getValue("surveystyle/matrixcolor_bg"));
		fg = QColor(global::R.getValue("surveystyle/matrixcolor_fg"));
		fontStyle(global::R.getValue("surveystyle/matrixtextstyle"),
				  global::R.getValue("surveystyle/matrixtextsize"),
				  font
				  );
		alignment = align(global::R.getValue("surveystyle/matrixtextalign"));

	}
	else if(t == tip::ItemMatrixProblem )
	{
		bg = QColor(global::R.getValue("surveystyle/matrixproblemcolor_bg"));
		fg = QColor(global::R.getValue("surveystyle/matrixproblemcolor_fg"));
		fontStyle(global::R.getValue("surveystyle/matrixproblemtextstyle"),
				  global::R.getValue("surveystyle/matrixproblemtextsize"),
				  font
				  );

		alignment = align(global::R.getValue("surveystyle/matrixproblemtextalign"));
	}
	else if(t == tip::ItemProblem )
	{
		bg = QColor(global::R.getValue("surveystyle/problemcolor_bg"));
		fg = QColor(global::R.getValue("surveystyle/problemcolor_fg"));
		fontStyle(global::R.getValue("surveystyle/problemtextstyle"),
				  global::R.getValue("surveystyle/problemtextsize"),
				  font
				  );

		alignment = align(global::R.getValue("surveystyle/problemtextalign"));
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

void SurveyTreeItemFactory::fontStyle(const QString & cstyle, const QString & size, QFont & f)
{
	QString style(cstyle.toLower());
	if(style!="normal")
	{
		f.setItalic( style.contains("italic") );
		f.setBold( style.contains("bold") );
	}

	f.setPointSize( size.toInt() );
}

Qt::Alignment SurveyTreeItemFactory::align(const QString &ca)
{
	QString a(ca.toLower());
	if(a=="right")
		return Qt::AlignRight;
	else if(a=="center")
		return Qt::AlignCenter;

	return Qt::AlignLeft;

}

END_NS
