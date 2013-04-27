#include "WobblerWidget.h"

#include "ImageFxFactory.h"

#include <QtGui>

WobblerWidget::WobblerWidget(const QImage & img,
					   qreal amplitude,
					   qreal frequency,
					   qreal speed,
					   QWidget *parent)

: QWidget(parent),
	mImgOriginal(img),
	mAmp(amplitude),
	mFreq(frequency),
	mCount(0),
	mSpeed(speed)
{

	setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred);
	resize(img.size());
	startTimer(20);
}

static const qreal Pi = 3.14159265;
static const qreal ToRad = Pi/180;

QSize WobblerWidget::sizeHint() const
{
	int w = mImg.width(),
		h = mImg.height(),
		a = 2 * ((int)mAmp+1);

	return QSize(w+a, 2*h );
}

void WobblerWidget::resizeEvent(QResizeEvent * e)
{

	int w = e->size().width(),
		h = e->size().height(),
		a = 2* ((int)mAmp+1);

	qDebug("w: %u, h: %u", w,h);
	if(w==0 || h==0)
	{

		e->ignore();
		return;
	}

	mImg = mImgOriginal.scaled(w,h/2,
								Qt::IgnoreAspectRatio );

	if(mImg.isNull())
		qDebug("Null image");

	mImgReflected =
			ImageFxFactory::createReflection(mImg)
			.scaledToWidth(w-a);
	mImgReflected = ImageFxFactory::createBlur(mImgReflected,
											   mImgReflected.rect(),
											   3
											   );
	mImgWobble = QImage(	w + a,h,
						QImage::Format_ARGB32_Premultiplied);

}

void WobblerWidget::paintEvent(QPaintEvent * )
{

	// wobble fx
	int h= mImgReflected.height();
	int w = mImgReflected.width();

	// clear image (transparent)
	mImgWobble.fill( qRgba(0,0,0,0) );


	qreal radfreq = ToRad*mFreq;
	qreal s = .0f;
	for(int y=0; y<h; ++y)
	{
		QRgb * line = (QRgb*)mImgReflected.scanLine(y);
		s = qSin( (( (int)mCount + y)%360)*radfreq ) * mAmp;
		for(int x=0; x<w; ++x)
		{
			mImgWobble.setPixel(((int)mAmp+1)+x+s,y,line[x]);
		}
	}

	// start painting
	QPainter p(this);
	p.drawImage(0,0, mImg);
	p.drawImage(0,mImg.height(),mImgWobble);
}

void WobblerWidget::timerEvent(QTimerEvent * e)
{

	Q_UNUSED(e);

	mCount+=mSpeed;
	update(mImgWobble.rect());

}
