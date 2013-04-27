#include "LineEdit.h"
#include "global.h"
#include "Overlay.h"

#include <QtGui>

START_NS

LineEdit::LineEdit(QWidget * parent)
	: QLineEdit(parent)
{

	mOverlay = new Overlay(this);
	mOverlay->setObjectName("LineEdit");
	/*
	QFont f = mOverlay->font();
	f.setPointSize(10);
	f.setBold(true);

	mOverlay->setFont( f );
	*/
	mOverlay->setText( tr("Enter your text") );

	connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(onTextChanged(const QString&)) );
}

void LineEdit::onTextChanged(const QString & text )
{
	mOverlay->setVisible( text.isEmpty() );
}

void LineEdit::showEvent(QShowEvent *)
{
	overlay()->center();
}

void LineEdit::resizeEvent(QResizeEvent *)
{
	overlay()->center();
}

void LineEdit::moveEvent(QMoveEvent *)
{
	overlay()->center();
}



END_NS
