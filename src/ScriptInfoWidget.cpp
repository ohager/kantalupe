#include "ScriptInfoWidget.h"
#include "global.h"
#include <QtGui>

#include "PlainTextEdit.h"
#include "LineEdit.h"
#include "Overlay.h"
#include "Script.h"

START_NS



ScriptInfoWidget::ScriptInfoWidget(QWidget *parent) :
    QWidget(parent)
{
	setupUi();
}

QString ScriptInfoWidget::getDescription() const
{
	return mDescription->toPlainText();
}
void  ScriptInfoWidget::setDescription(const QString & d)
{
	mDescription->setPlainText(d);
}

QString ScriptInfoWidget::getAuthor() const
{
	return mAuthor->text();
}

void  ScriptInfoWidget::setAuthor(const QString &a)
{
	mAuthor->setText(a);
}

QString ScriptInfoWidget::getVersion() const
{
	return mVersion->text();
}

void  ScriptInfoWidget::setVersion(const QString &v)
{
	mVersion->setText(v);
}

QDate ScriptInfoWidget::getLastEdited() const
{
	return QDate::fromString(mLastEdited->text(), global::DateFormat );
}

void  ScriptInfoWidget::setLastEdited(const QDate& d)
{
	mLastEdited->setText( d.toString( global::DateFormat ) );
}

QString ScriptInfoWidget::getName() const
{
	return mName->text();
}

void  ScriptInfoWidget::setName(const QString &n)
{
	mName->setText(n);
}


int ScriptInfoWidget::getApiLevel() const
{
	return mApiLevel->property("apilevel").toInt();
	//return mApiLevel->itemData( mApiLevel->currentIndex() ).toInt();
}

void  ScriptInfoWidget::setApiLevel(int apilevel)
{
	// first and last api level item
	mApiLevel->setText( QString("API Level %1").arg(apilevel) );
	mApiLevel->setProperty("apilevel", QString::number(apilevel) );
	/*
	if(apilevel>0 && apilevel<=1)
		mApiLevel->setCurrentIndex(apilevel-1);
	*/
}





void ScriptInfoWidget::setupUi()
{
	QBoxLayout * layout = new QVBoxLayout(this);
	QLayout * hlayout1 = new QHBoxLayout();

	mDescription = new PlainTextEdit(this);
	mDescription->overlay()->setText( tr("Enter the script's description") );
	mDescription->setToolTip(tr("Script description"));

	mAuthor = new LineEdit(this);
	mAuthor->overlay()->setText( tr("Enter script Author's name") );
	mAuthor->setToolTip(tr("Script author"));

	mName = new LineEdit(this);
	mName->overlay()->setText( tr("Enter script's name") );
	mName->setToolTip(tr("Script name"));

	mVersion = new LineEdit(this);
	mVersion->overlay()->setText( tr("Enter script version") );
	mVersion->setValidator( new QRegExpValidator( QRegExp("\\d+[\\.\\d+]{0,2}"), mVersion ) );
	mVersion->setToolTip(tr("Script version"));

	mLastEdited = new LineEdit(this);
	mLastEdited->setText(QDate::currentDate().toString(global::DateFormat));
	mLastEdited->setEnabled(false); // not editable
	mLastEdited->setToolTip(tr("Last edit date"));


	mApiLevel = new LineEdit(this);
	mApiLevel->setEnabled(false); // not editable
	mApiLevel->setToolTip(tr("Script's API Level"));

	// we start adding level 1 at index 0
	//mApiLevel->addItem("API Level 1", QVariant(1));

	hlayout1->addWidget(mVersion);
	hlayout1->addWidget(mApiLevel);
	hlayout1->addWidget(mLastEdited);

	layout->addWidget(mName);
	layout->addWidget(mDescription);
	layout->addWidget(mAuthor);
	layout->addLayout(hlayout1);

}



void ScriptInfoWidget::fromScript(const Script & s)
{
	setName(s.name);
	setDescription(s.description);
	setAuthor(s.author);
	setLastEdited(s.lastEdited);
	setVersion( s.version );
	setApiLevel( s.apilevel );

}

Script ScriptInfoWidget::toScript() const
{
	Script s;
	s.author = getAuthor();
	s.name = getName();
	s.description = getDescription();
	s.version = getVersion();
	s.lastEdited = getLastEdited();
	s.apilevel = getApiLevel();
	return s;
}

// ----------------------- events -------------------------------
void ScriptInfoWidget::showEvent(QShowEvent *)
{

}

END_NS

