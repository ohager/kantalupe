#ifndef IMAGEFXFACTORY_H
#define IMAGEFXFACTORY_H

#include <QObject>
#include <QImage>

/**
  A utility class that creates different (static) graphic effects from
  images.
  @author O. Haeger
  */
class ImageFxFactory : public QObject
{
public:
    explicit ImageFxFactory(QObject *parent = 0);

	/**
	  Creates a mirrored reflection of passed image.
	  @param image The name of the file
	  @return A mirrored reflection of the input image.
	  */
	static QImage createReflection(const QImage & image);


	/**
	  Creates a blur effect on image.
	  @param img The original image
	  @param rect The specified are for blur effect
	  @param radius The 'intensity' of the blur
	  @param alphaOnly Whether the blur shall be applied to alpha channel only, or not.
	  @return The blurred image
	  */
	static QImage createBlur(const QImage& image,
									 const QRect& rect,
									 int radius,
									 bool alphaOnly=false);

	/**
	  Creates a vertically distorted image
	  @param image The original image
	  @param freq The frequency, i.e. the 'amount of waves'
	  @param amp The amplitude, i.e. the 'depth of a wave'
	  @return The distorted image
	  @note The returned image is wider than the orignal
	  @see createDistortionH()
	  */
	static QImage createDistortionV(const QImage & image,
									qreal freq,
									qreal amp
									);

	/**
	  Creates a horizontally distorted image
	  @param image The original image
	  @param freq The frequency, i.e. the 'amount of waves'
	  @param amp The amplitude, i.e. the 'depth of a wave'
	  @return The distorted image
	  @note The returned image is taller than the orignal
	  @see createDistortionV()
	  */
	static QImage createDistortionH(const QImage & image,
									qreal freq,
									qreal amp
									);
};

#endif // IMAGEFXFACTORY_H
