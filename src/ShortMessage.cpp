#include "ShortMessage.h"

#include <QtGui>

ShortMessage::ShortMessage(QWidget *parent) :
	QWidget(parent, Qt::FramelessWindowHint), mDuration(DefaultDuration), mFade(0)
{
	setup();

}

ShortMessage::ShortMessage(QWidget * parent, const QString &message, int duration) :
	QWidget(parent, Qt::FramelessWindowHint), mDuration(duration), mFade(0)
{
	setup();
	setMessage(message);
}

void ShortMessage::setup(){
	// getting root widget

	QWidget * p = parentWidget();
	while(p->parentWidget())
	{
		p = p->parentWidget();
	}
	setParent(p);
	QFont f(font());
	f.setPointSize(16);
	setFont(f);

}

// static
void ShortMessage::showMessage(QWidget * parent, const QString & m, int d)
{
	ShortMessage * sm = new ShortMessage(parent, m,d);
	connect(sm, SIGNAL(finished()), sm, SLOT(deleteLater()));
	sm->show();

}

void ShortMessage::setMessage(const QString & m)
{
	mMessage = m;

	// calcs with linebreaks !
	QSize s(fontMetrics().size(0, m));
	s+=QSize(8,8);
	resize( s );
}
const QString & ShortMessage::message() const { return mMessage; }
void ShortMessage::setDuration(int millies){ mDuration = millies; }
int ShortMessage::duration() const { return mDuration; }

int ShortMessage::fade() const { return mFade; }
void ShortMessage::setFade(int f)
{
	//qDebug("fade: %u", f);
	mFade = f;
	update();
}


// ------------------------------- SLOTS --------------------------

void ShortMessage::center()
{
	QWidget * w = ((QWidget*)parent());
	// center
	int x=(w->width() - width())/2;
	int y=(w->height() - height())/2;

	move( x,y );
}




// ------------------------ events ------------------------------
void ShortMessage::resizeEvent(QResizeEvent * e)
{
	Q_UNUSED(e);
	center();
}

void ShortMessage::showEvent(QShowEvent * e)
{
	Q_UNUSED(e);
	center();
	fadeIn();
	startTimer(duration());

}

void ShortMessage::timerEvent(QTimerEvent *e)
{
	fadeOut();
	killTimer(e->timerId());
	qDebug("Message closed");
}

void ShortMessage::paintEvent(QPaintEvent * e)
{



	/*
	QRect r(0,0,width(),height());
	QPixmap transparent(size());
	transparent.fill();
	QPainter p(&transparent);
	QPen pen;
	pen.setColor(QColor(255,255,255,f));
	p.setPen(pen);
	p.setCompositionMode(QPainter::CompositionMode_SourceOver);
	p.setFont( font() );
	p.drawText(r , Qt::AlignCenter, mMessage);
	p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
	p.fillRect(transparent.rect(), QColor(0, 0, 0, f));

	p.end();

	pw.drawPixmap(0,0, transparent);
	*/

	// Actual fading
	int f=fade();

	QPainter painter(this);

	painter.setRenderHint(QPainter::Antialiasing);
	painter.setOpacity(f/255.0f);

  // created rounded rect
	QPainterPath roundrect;
	roundrect.addRoundRect(0,0,width(), height(), 25);
	painter.setClipPath(roundrect);
	QRegion maskregion = painter.clipRegion();

	// mask the widget
	setMask(maskregion);
	painter.fillPath(roundrect,QColor(96,96,96,180));

	// create text
	QPen pen;
	pen.setColor(QColor(255,255,255));
	painter.setPen(pen);
	painter.setFont( font() );
	painter.drawText( rect() , Qt::AlignCenter, mMessage);

}

// ---------------------- SLOTS ------------------------------------

void ShortMessage::fadeIn()
{
	// Start animate this class

	 QPropertyAnimation* anim = new QPropertyAnimation(this, "fade");
	 anim->setDuration(300);
	 anim->setStartValue(0); // from fully visible
	 anim->setEndValue(255); // to invisible
	 anim->setEasingCurve(QEasingCurve::InOutQuad);

	 //QObject::connect(anim, SIGNAL(finished()), this, SLOT(show()));

	 anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void ShortMessage::fadeOut()
{

	QPropertyAnimation* anim = new QPropertyAnimation(this, "fade");
	anim->setDuration(300);
	anim->setStartValue(255); // from fully visible
	anim->setEndValue(0); // to invisible
	anim->setEasingCurve(QEasingCurve::InOutQuad);

	//QObject::connect(anim, SIGNAL(finished()), this, SLOT(hide()));
	QObject::connect(anim, SIGNAL(finished()), this, SIGNAL(finished()));
	anim->start(QAbstractAnimation::DeleteWhenStopped);
}



