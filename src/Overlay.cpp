#include "Overlay.h"
#include "global.h"

#include <QtGui>

START_NS

Overlay::Overlay(QWidget *parent) :
	QLabel(parent)
{
	//setDisabled(true);
	setAttribute(Qt::WA_TransparentForMouseEvents);
}


void Overlay::center()
{
	raise();

	QWidget * w = ((QWidget*)parent());
	// center
	int x=(w->width() - width())/2;
	int y=(w->height() - height())/2;

	adjustSize();
	move( x,y );
}


END_NS
