#ifndef WOBBLERWIDGET_H
#define WOBBLERWIDGET_H

#include <QWidget>
#include <QImage>

/**
  The wobbler widget is a widget, that takes any QImage and
  'casts' a water wobbling effect on that image's reflection.
  @note When resizing, the size does not count for the original image only, but
  for the reflection either. The height of the widget is @e twice its original image.
  @author O. Haeger

  */
class WobblerWidget : public QWidget
{
public:
	/**
	  @param img The image for the effect
	  @param amplitude The intensity of the wobble waves (x-axis).
			They are considered as pixels, but fractions of pixels are allowed either.
	  @param frequency The 'amount' of waves along the image's reflection height (y-axis)
	  @param speed A value that influences the animation speed.
	  @param parent The parent widget
	  */
	explicit WobblerWidget(const QImage & img,
						   qreal amplitude = 10,
						   qreal frequency = 7.25f,
						   qreal speed = 1.0f,
						   QWidget *parent = 0);

	inline void setAmplitude(qreal a) { mAmp = a; }
	inline qreal amplitude() const { return mAmp; }
	inline void setFrequency(qreal f) { mFreq = f; }
	inline qreal frequency() const { return mFreq; }
	inline void setSpeed(qreal s) { mSpeed = s; }
	inline qreal speed() const { return mSpeed; }

	QSize sizeHint() const;

protected:
	void resizeEvent(QResizeEvent * e);
	void paintEvent(QPaintEvent*);
	void timerEvent(QTimerEvent *);
private:
	QImage mImgOriginal, mImg, mImgReflected, mImgWobble;
	qreal mAmp, mFreq, mCount, mSpeed;
};

#endif // WOBBLERWIDGET_H
