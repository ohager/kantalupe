#include "SurveyEditorMetaInfoPage.h"
#include "global.h"
#include "LineEdit.h"
#include "PlainTextEdit.h"
#include "Overlay.h"

#include "TreeItem.h"
#include "TreeItemProtocol.h"
#include "SignalBlocker.h"

#include <QtGui>

START_NS

SurveyEditorMetaInfoPage::SurveyEditorMetaInfoPage(QWidget * parent)
	: EditorBasePage(parent) {

	setupUi();
}

SurveyEditorMetaInfoPage::~SurveyEditorMetaInfoPage()
{

}

bool SurveyEditorMetaInfoPage::isAcceptingMime(const QMimeData *m) const
{
	return false;
}


void SurveyEditorMetaInfoPage::commit(TreeItem * item) const
{
	EditorBasePage::commit(item);


	if(item->getItemType()==tip::ItemSurvey)
	{
		Survey obj;
		tip::extract(item, obj);
		obj.affiliation.firstname = mFirstNameEdit->text();
		obj.affiliation.lastname = mLastNameEdit->text();
		obj.affiliation.email = mEmailEdit->text();
		obj.affiliation.telephone = mPhoneEdit->text();

		obj.texts.remind = mRemindTextEdit->toPlainText();
		obj.texts.thank = mThankTextEdit->toPlainText();
		obj.texts.welcome = mWelcomeTextEdit->toPlainText();
		tip::incept(obj, item);
	}

}
void SurveyEditorMetaInfoPage::update(TreeItem * item)
{
	EditorBasePage::update(item);

	SignalBlocker b( QList<QObject*>() <<
					mFirstNameEdit <<
					mLastNameEdit <<
					mEmailEdit <<
					mPhoneEdit <<
					mWelcomeTextEdit <<
					mRemindTextEdit <<
					mThankTextEdit
					);
	Q_UNUSED(b)

	if(item->getItemType() == tip::ItemSurvey)
	{
		Survey obj;
		tip::extract(item, obj);
		mFirstNameEdit->setText( obj.affiliation.firstname );
		mLastNameEdit->setText( obj.affiliation.lastname );
		mEmailEdit->setText( obj.affiliation.email );
		mPhoneEdit->setText( obj.affiliation.telephone );

		mRemindTextEdit->setPlainText( obj.texts.remind );
		mWelcomeTextEdit->setPlainText( obj.texts.welcome );
		mThankTextEdit->setPlainText( obj.texts.thank );

		// manual setup as signals must be blocked!
		mFirstNameEdit->overlay()->setVisible( obj.affiliation.firstname.isEmpty() );
		mLastNameEdit->overlay()->setVisible( obj.affiliation.lastname.isEmpty() );
		mEmailEdit->overlay()->setVisible( obj.affiliation.email.isEmpty() );
		mPhoneEdit->overlay()->setVisible( obj.affiliation.telephone.isEmpty() );

		mRemindTextEdit->overlay()->setVisible( obj.texts.remind.isEmpty() );
		mWelcomeTextEdit->overlay()->setVisible( obj.texts.welcome.isEmpty() );
		mThankTextEdit->overlay()->setVisible( obj.texts.thank.isEmpty() );

	}
}

void SurveyEditorMetaInfoPage::setupUi()
{

	QLayout * layout = new QVBoxLayout();

	QGroupBox * affiliation = new QGroupBox(this);
	affiliation->setTitle(tr("Affiliation"));

	QGridLayout * afflayout = new QGridLayout(affiliation);
	mFirstNameEdit = new LineEdit(this);

	mFirstNameEdit->overlay()->setText(tr("Author's first name"));
	mLastNameEdit = new LineEdit(this);
	mLastNameEdit->overlay()->setText(tr("Author's last Name"));
	mEmailEdit = new LineEdit(this);
	mEmailOverlayTextBuffer = tr("Author's email address");
	mEmailEdit->overlay()->setText(mEmailOverlayTextBuffer);
	mEmailEdit->setValidator( new QRegExpValidator(
								 QRegExp("^[\\w-]+(?:\\.[\\w-]+)*@(?:[\\w-]+\\.)+[a-zA-Z]{2,7}$"),
								 mEmailEdit));
	mPhoneEdit = new LineEdit(this);
	mPhoneEdit->overlay()->setText(tr("Author's Phone number"));

	afflayout->addWidget(mFirstNameEdit, 0, 0);
	afflayout->addWidget(mLastNameEdit, 0, 1);
	afflayout->addWidget(mEmailEdit, 1, 0);
	afflayout->addWidget(mPhoneEdit, 1, 1);

	connect(mEmailEdit, SIGNAL(textChanged(const QString &)), this, SLOT(onValidateEmail(const QString &)));

	QTabWidget * textswidget = new QTabWidget(this);
	textswidget->setLayout( new QHBoxLayout() );
	textswidget->layout()->setContentsMargins(0,0,0,0);

	mWelcomeTextEdit = new PlainTextEdit();
	mWelcomeTextEdit->overlay()->setText(tr("Enter welcome text\nfor this survey"));
	mRemindTextEdit = new PlainTextEdit();
	mRemindTextEdit->overlay()->setText(tr("Enter remind text\nfor this survey"));
	mThankTextEdit = new PlainTextEdit();
	mThankTextEdit->overlay()->setText(tr("Enter thank note\nfor this survey"));


	textswidget->addTab(mWelcomeTextEdit, tr("Welcome"));
	textswidget->addTab(mRemindTextEdit, tr("Remind"));
	textswidget->addTab(mThankTextEdit, tr("Thank"));

	layout->addWidget( affiliation );
	layout->addWidget( textswidget );

	setLayout(layout);

	setCommitDelay(1000);
	connect(mFirstNameEdit, SIGNAL(textChanged(QString)), this, SLOT(delayedCommit()));
	connect(mLastNameEdit, SIGNAL(textChanged(QString)), this, SLOT(delayedCommit()));
	connect(mEmailEdit, SIGNAL(textChanged(QString)), this, SLOT(delayedCommit()));
	connect(mPhoneEdit, SIGNAL(textChanged(QString)), this, SLOT(delayedCommit()));
	connect(mWelcomeTextEdit, SIGNAL(textChanged()), this, SLOT(delayedCommit()));
	connect(mRemindTextEdit, SIGNAL(textChanged()), this, SLOT(delayedCommit()));
	connect(mThankTextEdit, SIGNAL(textChanged()), this, SLOT(delayedCommit()));


}

// ------------------------------------ slots ------------------------------------------------

void SurveyEditorMetaInfoPage::onValidateEmail(const QString & constemail)
{
	int pos=0;
	Overlay * overlay = mEmailEdit->overlay();
	overlay->resize( mEmailEdit->size() );
	overlay->move( -4,0 ); // to gain a small gap on right side off parent widget
	QString email(constemail);

	switch(mEmailEdit->validator()->validate(email,pos))
	{
	case QValidator::Intermediate:
	case QValidator::Invalid:
		overlay->setPixmap(QPixmap(global::R.getValue("icon/false")).scaledToHeight(12, Qt::SmoothTransformation));
		overlay->setAlignment(Qt::AlignRight | Qt::AlignVCenter );
		overlay->show();
		break;
case QValidator::Acceptable:
		overlay->setText(mEmailOverlayTextBuffer);
		mEmailEdit->overlay()->setVisible( mEmailEdit->text().isEmpty() );
		overlay->setAlignment(Qt::AlignCenter);
		break;
	}
}


END_NS


