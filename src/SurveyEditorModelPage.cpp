#include "SurveyEditorModelPage.h"
#include "SurveyModelViewer.h"
#include "WidgetExtension.h"
#include "global.h"

#include <QtGui>


START_NS

SurveyEditorModelPage::SurveyEditorModelPage(QWidget * parent)
	: EditorBasePage(parent), mSurveyModelViewer(0x0) {

	setupUi();
}

SurveyEditorModelPage::~SurveyEditorModelPage()
{

}

bool SurveyEditorModelPage::isAcceptingMime(const QMimeData *m) const
{
	// we will accept mime, yes!
	return false;
}


void SurveyEditorModelPage::commit(TreeItem * item) const
{
	EditorBasePage::commit(item);

	/* nothing to do ---- modelview is readonly */
}
void SurveyEditorModelPage::update(TreeItem * item)
{
	EditorBasePage::update(item);

	/* nothing to do ---- modelview is readonly */
}

void SurveyEditorModelPage::setupUi()
{
	QLayout * layout = new QVBoxLayout();


	mSurveyModelViewer =  new SurveyModelViewer(this);


	layout->addWidget(mSurveyModelViewer);
	setLayout(layout);

}


END_NS

