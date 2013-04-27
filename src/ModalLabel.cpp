#include "ModalLabel.h"
#include "global.h"

#include <QtGui>

START_NS

ModalLabel::ModalLabel(QMainWindow * window) :
	QWidget(window),
	mColorFg(Qt::transparent),
	mColorBg(Qt::black),
	mPosition(TopLeft)
{
	setWindowOpacity(0.0f);
	setup();

}

ModalLabel::ModalLabel(QMainWindow * window, const QString &message) :
	QWidget(window),
	mColorFg(Qt::transparent),
	mColorBg(Qt::black),
	mPosition(TopLeft)
{
	setup();
	setText(message);
}

void ModalLabel::setup(){
	// getting root widget

	/*
	QWidget * p = parentWidget();
	while(p->parentWidget())
	{
		p = p->parentWidget();
	}
	setParent(p);
	*/
	QFont f(font());
	f.setPointSize(16);
	setFont(f);

}

void ModalLabel::setForegroundColor(const QColor & c){ mColorFg =c; }
const QColor ModalLabel::foregroundColor() const { return mColorFg; }

void ModalLabel::setBackgroundColor(const QColor & c) { mColorBg =c; }
const QColor ModalLabel::backgroundColor() const{ return mColorBg; }


void ModalLabel::setText(const QString & m)
{
	mMessage = m;

	// calcs with linebreaks !
	QSize s(fontMetrics().size(0, m));
	s+=QSize(8,8);
	resize( s );
}

void ModalLabel::setFont(const QFont & f)
{
	QWidget::setFont(f);
	setText(text()); // resize
}

const QString & ModalLabel::text() const { return mMessage; }


void ModalLabel::setPosition(Position p) {
	mPosition = p;
	move( calcPosition(p) );
}

ModalLabel::Position ModalLabel::position() const { return mPosition; }



QPoint ModalLabel::calcPosition(ModalLabel::Position p)
{

	QWidget * widget = parentWidget();

	int x = 0,
		y = 0,
		w = width(),
		h = height(),
		pw = widget->width(),
		ph = widget->height();
	static const int Margin = 8;
	switch(p)
	{
	case TopLeft:
		x=y=Margin;
		break;
	case TopCenter:
		x = (pw-w)/2;
		y = Margin;
		break;
	case TopRight:
		x = pw-w-Margin;
		y = Margin;
		break;
	case CenterLeft:
		x = Margin;
		y = (ph-h)/2;
		break;
	case Center:
		x = (pw-w)/2;
		y = (ph-h)/2;
		break;
	case CenterRight:
		x = pw-w-Margin;
		y = (ph-h)/2;
		break;
	case BottomLeft:
		x = Margin;
		y = ph-h-Margin;
		break;
	case BottomCenter:
		x = (pw-w)/2;
		y = ph-h-Margin;
		break;
	case BottomRight:
		x = pw-w-Margin;
		y = ph-h-Margin;
		break;
	}
	return QPoint(x,y);
}



// ------------------------ events ------------------------------
void ModalLabel::resizeEvent(QResizeEvent * e)
{
	Q_UNUSED(e);
	move( calcPosition(position()) );
	raise();
}

void ModalLabel::showEvent(QShowEvent * e)
{
	Q_UNUSED(e);
	move( calcPosition(position()) );
	raise();
}


void ModalLabel::paintEvent(QPaintEvent * e)
{

	QPainter painter(this);
	painter.save();
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

	painter.fillRect( rect(), backgroundColor() );
	// create text
	QPen pen;
	pen.setColor( foregroundColor() );
	painter.setPen(pen);
	painter.setFont( font() );
	painter.drawText( rect() , Qt::AlignCenter, text() );
	painter.restore();
}


END_NS

