#include "DockWidget.h"
#include "global.h"
#include "ContentFrame.h"
#include <QtGui>

START_NS



// ------------------------------------------
#define CONTENT(w) static_cast<k::ContentFrame*>(w)

DockWidget::DockWidget(QWidget *parent) :
	QDockWidget(parent)
{

	setContentsMargins(0,0,0,0);
	layout()->setMargin(0);
	layout()->setSpacing(0);
	setWidget(new ContentFrame(this) );
	setFeatures( NoDockWidgetFeatures );
	setTitleBarWidget( new QWidget(this) ); // empty
}

void DockWidget::setContentWidth(int w)
{
	ContentFrame * c = CONTENT(widget());
	c->resize( w, c->height());
}

int DockWidget::contentWidth() const
{
	return widget()->width();
}

k::ContentFrame * DockWidget::content() const
{
	return CONTENT(widget());
}

void DockWidget::setContent(k::ContentFrame * c)
{
	if(widget())
	{
		widget()->deleteLater();
	}

	setWidget(c);
}

// protected
void DockWidget::setWidget(QWidget * w)
{
	QDockWidget::setWidget(w);
}



END_NS


