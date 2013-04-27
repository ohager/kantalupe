#include "PlainTextEdit.h"
#include "global.h"
#include "Overlay.h"

#include <QtGui>

START_NS

PlainTextEdit::PlainTextEdit(QWidget * parent)
	: QPlainTextEdit(parent)
{

	mOverlay = new Overlay(this);
	mOverlay->setObjectName("plaintextedit");
	/*
	 shall be edited by qss
	QFont f = mOverlay->font();
	f.setPointSize(10);
	f.setBold(true);

	mOverlay->setFont( f );
	*/
	mOverlay->setText( tr("Enter your text") );

	connect(this, SIGNAL(textChanged()), this, SLOT(onTextChanged()) );
}

void PlainTextEdit::onTextChanged()
{

	mOverlay->setVisible( document()->toPlainText().isEmpty() );
}

void PlainTextEdit::showEvent(QShowEvent *)
{
	overlay()->center();
}

void PlainTextEdit::resizeEvent(QResizeEvent *)
{
	overlay()->center();
}

void PlainTextEdit::moveEvent(QMoveEvent *)
{
	overlay()->center();
}



END_NS
