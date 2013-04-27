#include "AbstractEditor.h"
#include "global.h"

#include <QtGui>

START_NS

AbstractEditor::AbstractEditor(QWidget * parent)
	: QWidget(parent),
	  mPageSelector(new QListWidget(this) ),
	  mPagesWidget(new QStackedWidget(this) )

{
	mPageSelector = new QListWidget();
	mPageSelector->setObjectName("pageSelector");
	mPageSelector->setSelectionMode(QAbstractItemView::SingleSelection);
	mPageSelector->setViewMode(QListView::IconMode);
	mPageSelector->setIconSize(QSize(48, 48));
	//mPageSelector->setUniformItemSizes(true);
	mPageSelector->setMovement(QListView::Static);
	mPageSelector->setFixedHeight(90);
	mPageSelector->setSpacing(8);
	mPageSelector->setWrapping(false);
	mPageSelector->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	mPageSelector->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );


	connect(mPageSelector,
			SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
			this, SLOT(changePage(QListWidgetItem *, QListWidgetItem*)));

	QVBoxLayout *vlayout= new QVBoxLayout(this);
	vlayout->setMargin(0);
	vlayout->setSpacing(0);
	vlayout->addWidget(mPageSelector);
	vlayout->addWidget(mPagesWidget);

}

AbstractEditor::~AbstractEditor()
{

}

int AbstractEditor::addPage(QWidget * page, const QIcon & icon, const QString & text, const QString & tooltip)
{
	QFont f;
	f.setBold(true);

	QListWidgetItem * pageButton = new QListWidgetItem(icon,text, mPageSelector);
	pageButton->setFont(f);
	pageButton->setToolTip(tooltip);
	pageButton->setTextAlignment(Qt::AlignHCenter);
	pageButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	return mPagesWidget->addWidget(page);
}


void AbstractEditor::aboutToChangePage(QWidget * page)
{

}


// ---------------------------------- slots ------------------------------------
void AbstractEditor::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
	qDebug("Page change request: from %i to %i", mPageSelector->row(previous), mPageSelector->row(current));
	if (!current)
			current = previous;

	int index =mPageSelector->row(current);
	aboutToChangePage(mPagesWidget->widget(index));
	mPagesWidget->setCurrentIndex(index);
}







END_NS
