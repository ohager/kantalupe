#include "ImageItem.h"
#include "global.h"
#include <QPropertyAnimation>

#include <QtGui>

START_NS

ImageItem::ImageItem(const QPixmap & img, QWidget *parent) :
QWidget(parent,Qt::FramelessWindowHint),
		mFade(0),
		mIsAnimationFinished(true),
		mPixmapOrig(img)
{
	resize(parent->size());
	setFade(mFade);

}

ImageItem::ImageItem(const QPixmap & img,const QString & infotext, QWidget * parent) :
		QWidget(parent,Qt::FramelessWindowHint),
				mFade(0),
				mIsAnimationFinished(true),
				mPixmapOrig(img)
{
	resize(parent->size());
	setFade(mFade);
}

ImageItem::~ImageItem()
{
	qDebug("Image item deleted");
}


void ImageItem::setInfoText(const QString & text)
{
	mInfoText = text;
	update();
}

const QString & ImageItem::infoText() const
{
	return mInfoText;
}



int ImageItem::fade() const { return mFade; }
void ImageItem::setFade(int f)
{
	qDebug("fade: %u", f);
	mFade = f;
	setVisible(mFade);
	/*
	if(isVisible())
	{
		grabMouse();
	}
	else
	{
		releaseMouse();
	}
	*/
	update();
}


void ImageItem::center()
{

	QWidget * w = ((QWidget*)parent());
	// center
	int x=(w->width() - width())/2;
	int y=(w->height() - height())/2;

	move( x,y );
}


// ---------------------- EVENTS -----------------------------------
void ImageItem::showEvent(QShowEvent * e)
{
	Q_UNUSED(e);
	center();
}

void ImageItem::moveEvent(QMoveEvent * e)
{
	Q_UNUSED(e);
	//center();
}

void ImageItem::resizeEvent(QResizeEvent * e)
{
	qDebug("resized...");
	if(mPixmapOrig.height() > e->size().height() ||
	   mPixmapOrig.width() > e->size().width()
	   )
	{
		mPixmap = mPixmapOrig.scaled(e->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
	}
	else
	{
		mPixmap = mPixmapOrig;
	}

	resize(mPixmap.size()); // set widget size to pixmap size
	center();
}

void ImageItem::mousePressEvent(QMouseEvent *e)
{
	Q_UNUSED(e);

	if(!mIsAnimationFinished) // still animating
		return;

	fadeOut();
}


void ImageItem::paintEvent(QPaintEvent * e)
{
	QPainter pw(this);


	// Actual fading
	QPixmap transparent(mPixmap.size());
	transparent.fill(QColor(200,200,200,128));
	QPainter p(&transparent);
	p.setCompositionMode(QPainter::CompositionMode_SourceOver);
	p.drawPixmap(0,0, mPixmap);
	if(!mInfoText.isEmpty())
	{
		p.setPen( Qt::black );
		p.drawText(4,4,transparent.rect().width(),transparent.rect().height(),
				   Qt::AlignTop | Qt::TextWordWrap,
				   mInfoText);
	}
	p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
	p.fillRect(transparent.rect(), QColor(0, 0, 0, mFade));

	p.end();

	pw.drawPixmap(0,0, transparent);



}

// ---------------------- SLOTS ------------------------------------
void ImageItem::animationFinished()
{
	mIsAnimationFinished=true;
	if(!fade())
		emit fadedOut();
	else
		emit fadedIn();
}

void ImageItem::fadeIn()
{
	// Start animate this class

	 QPropertyAnimation* anim = new QPropertyAnimation(this, "fade");
	 anim->setDuration(300);
	 anim->setStartValue(0); // from fully visible
	 anim->setEndValue(255); // to invisible
	 anim->setEasingCurve(QEasingCurve::InOutQuad);

	 QObject::connect(anim, SIGNAL(finished()), this, SLOT(animationFinished()));

	 mIsAnimationFinished =true;
	 anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void ImageItem::fadeOut()
{

	QPropertyAnimation* anim = new QPropertyAnimation(this, "fade");
	anim->setDuration(300);
	anim->setStartValue(255); // from fully visible
	anim->setEndValue(0); // to invisible
	anim->setEasingCurve(QEasingCurve::InOutQuad);

	QObject::connect(anim, SIGNAL(finished()), this, SLOT(animationFinished()));

	mIsAnimationFinished =true;
	anim->start(QAbstractAnimation::DeleteWhenStopped);
}




END_NS
