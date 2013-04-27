#include "SurveyDataEditor.h"

#include "SurveyEditorGeneratorPage.h"
#include "SurveyEditorScriptPage.h"
#include "SurveyEditorMetaInfoPage.h"
#include "SurveyEditorModelPage.h"

#include "global.h"
#include "Application.h"

#include <QtGui>

#include "TreeItem.h"
#include "TreeItemProtocol.h"

#include "ModalLabel.h"

#include "UserModeEvent.h"
#include "WidgetExtension.h"

START_NS


//---------------------------- Listener for wx ------------------------
class WxListenerSurveyDataEditor : public WxListenerDefault{
	public:
		void onUserModeChange(WidgetExtension *wx, UserModeEvent *e)
		{
			SurveyDataEditor * editor = (SurveyDataEditor *)wx->widget();
			editor->setScriptEditorVisible( e->userMode()==global::UserModeExpert );
		}
};
// -------------------------------------------------------------------

SurveyDataEditor::SurveyDataEditor(QWidget * parent)
	: QWidget(parent, 0x0),
	  mContentsWidget(0x0),
	  mPagesWidget(0x0),
	  mButtonModel(0x0),
	  mButtonMeta(0x0),
	  mButtonGenerator(0x0),
	  mButtonScript(0x0),
	  mPageModel(0),
	  mPageMeta(0),
	  mPageGenerator(0),
	  mPageScript(0)

{
	setupUi();
}

void SurveyDataEditor::setupUi()
{

	mContentsWidget = new QListWidget();
	mContentsWidget->setObjectName("surveyEditorMenu");
	mContentsWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	mContentsWidget->setViewMode(QListView::IconMode);
	mContentsWidget->setIconSize(QSize(48, 48));
	mContentsWidget->setUniformItemSizes(false);
	mContentsWidget->setMovement(QListView::Static);
	mContentsWidget->setFixedHeight(90);
	mContentsWidget->setSpacing(8);
	mContentsWidget->setWrapping(false);
	mContentsWidget->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	mContentsWidget->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
	//mContentsWidget->layout()->setAlignment(Qt::AlignCenter);




	mPagesWidget = new QStackedWidget();
	SurveyEditorScriptPage * scriptpage = new SurveyEditorScriptPage();
	SurveyEditorGeneratorPage * genpage = new SurveyEditorGeneratorPage();

	connect(scriptpage, SIGNAL(surveyGenerated(SurveyTree*)), this, SIGNAL(surveyGenerated(SurveyTree*)));
	connect(scriptpage,SIGNAL(scriptDeployed(QString)), genpage,SLOT(updateScriptList()));
	connect(genpage, SIGNAL(surveyGenerated(SurveyTree*)), this, SIGNAL(surveyGenerated(SurveyTree*)));
	// need to maintain the order according to createItems
	mPageMeta = mPagesWidget->addWidget( new SurveyEditorMetaInfoPage() );
	mPageModel = mPagesWidget->addWidget( new SurveyEditorModelPage() );
	mPageGenerator = mPagesWidget->addWidget( genpage );
	mPageScript = mPagesWidget->addWidget( scriptpage );


	createItems();
	mContentsWidget->setCurrentRow(0);

	QVBoxLayout *vlayout= new QVBoxLayout;
	vlayout->setMargin(0);
	vlayout->setSpacing(0);
	vlayout->addWidget(mContentsWidget);
	vlayout->addWidget(mPagesWidget);


	setLayout(vlayout);


	QFont font;
	font.setPixelSize(24);
	font.setBold(true);


	//setEnabled(false);
	//QTimer::singleShot(0,this, SLOT(openEditorCategory()));
}

void SurveyDataEditor::changePage(QListWidgetItem *current,
							QListWidgetItem *previous)
{
	qDebug("Page change request: from %i to %i", mContentsWidget->row(previous), mContentsWidget->row(current));
	if (!current)
			current = previous;

	mPagesWidget->setCurrentIndex(mContentsWidget->row(current));
}


void SurveyDataEditor::createItems()
{
	QFont f;
	f.setBold(true);

	mButtonMeta = new QListWidgetItem(mContentsWidget);
	mButtonMeta->setIcon(QIcon(global::R.getValue("icon/surveyeditorsurveymeta")));
	mButtonMeta->setText(tr("Metainfo"));
	mButtonMeta->setFont(f);
	mButtonMeta->setToolTip(tr("Edit the survey's Meta Information"));
	mButtonMeta->setTextAlignment(Qt::AlignHCenter);
	mButtonMeta->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	mButtonMeta->setHidden(false);

	// keep order to button's creation in setupUi()
	mButtonModel = new QListWidgetItem(mContentsWidget);
	mButtonModel->setIcon(QIcon(global::R.getValue("icon/surveyeditorsurvey")));
	mButtonModel->setText(tr("Model"));
	mButtonModel->setFont(f);
	mButtonModel->setToolTip(tr("Load model for survey"));
	mButtonModel->setTextAlignment(Qt::AlignHCenter);
	mButtonModel->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	mButtonModel->setHidden(false);


	mButtonGenerator = new QListWidgetItem(mContentsWidget);
	mButtonGenerator->setIcon(QIcon(global::R.getValue("icon/surveyeditorgenerator")));
	mButtonGenerator->setText(tr("Generator"));
	mButtonGenerator->setFont(f);
	mButtonGenerator->setToolTip(tr("Use generators to quickly create your survey"));
	mButtonGenerator->setTextAlignment(Qt::AlignHCenter);
	mButtonGenerator->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	mButtonGenerator->setHidden(false);

	mButtonScript = new QListWidgetItem(mContentsWidget);
	mButtonScript->setIcon(QIcon(global::R.getValue("icon/surveyeditorscript")));
	mButtonScript->setText(tr("Script"));
	mButtonScript->setFont(f);
	mButtonScript->setToolTip(tr("Edit the generator scripts"));
	mButtonScript->setTextAlignment(Qt::AlignHCenter);
	mButtonScript->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	mButtonScript->setHidden( kApp->userMode() == global::UserModeNovice );

	WidgetExtension * wx = new WidgetExtension(this, WidgetExtension::AlwaysVisible);
	wx->setListener(  new WxListenerSurveyDataEditor() );

	connect(mContentsWidget,
			SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
			this, SLOT(changePage(QListWidgetItem *, QListWidgetItem*)));
}


void SurveyDataEditor::openEditor(TreeItem * item)
{
	// simply delegate.
	// currently we do not have any item type dependent editing feature
	// we pass only the root item (survey type) to update
	// note: this might change in future
	TreeItem * surveyitem = item;
	while(surveyitem->getItemType() != tip::ItemSurvey )
	{
		surveyitem = (TreeItem*)surveyitem->parent();
		Q_ASSERT_X(surveyitem,"SurveyEditor::openEditor","There is no survey item!");
	}

	updateEditor(surveyitem);
}

void SurveyDataEditor::updateEditor(TreeItem * item)
{
	// broadcast
	for(int i=0; i< mPagesWidget->count(); ++i)
	{
		EditorBasePage * page = (EditorBasePage*)mPagesWidget->widget(i);
		page->update(item);
	}
}

void SurveyDataEditor::commit()
{
	// broadcast
	for(int i=0; i< mPagesWidget->count(); ++i)
	{
		((EditorBasePage*)mPagesWidget->widget(i))->commit();
	}
}


void SurveyDataEditor::setScriptEditorVisible(bool visible)
{
	mButtonScript->setHidden(!visible);
	if(!visible && mPagesWidget->currentIndex() == mPageScript)
		mPagesWidget->setCurrentIndex(mPageMeta);

}



END_NS
