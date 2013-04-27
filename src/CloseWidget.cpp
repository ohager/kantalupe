#include "CloseWidget.h"

#include <QPainter>
#include <QPaintEvent>


CloseWidget::CloseWidget(QWidget *parent) :
	QWidget(parent), mEntered(false)
{

	resize(24,24);

}


void CloseWidget::paintEvent(QPaintEvent * pe)
{
	QPainter p(this);


	QPen pen;
    if(mEntered)
    {
		pen.setColor(QColor(255,255,255,64));
		pen.setWidth(2);
    }
    else
    {
		pen.setColor(QColor(255,255,255,128));
		pen.setWidth(1);
    }


//    p.setPen(pen);
	const QSize  & s = size();
	p.drawRoundedRect(0,0,s.width(), s.height(),0.1,0.1,Qt::RelativeSize);
	p.drawLine(0,0,s.width(), s.height());
	p.drawLine(0,s.height(), s.width(), 0);
}

void CloseWidget::enterEvent(QEvent *)
{
    mEntered = true;
}

void CloseWidget::leaveEvent(QEvent *)
{
    mEntered = false;
}

void CloseWidget::mousePressEvent(QMouseEvent *)
{
    emit clicked();
}
