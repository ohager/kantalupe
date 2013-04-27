#include "ImageFxFactory.h"

#include <QImage>
#include <QLinearGradient>
#include <QPainter>
#include <QtCore>

#ifndef PI
#define PI 3.14159265f
#endif

#ifndef TO_RAD
#define TO_RAD PI/180
#endif

ImageFxFactory::ImageFxFactory(QObject *parent) :
    QObject(parent)
{
}


QImage ImageFxFactory::createReflection(const QImage & img)
{
	// create alpha channel
	QLinearGradient g = QLinearGradient(
			QPoint(0,0), QPoint(0,img.height()) );

	g.setColorAt(0.5,Qt::black);
	g.setColorAt(0,Qt::white);

	QImage mask( img.size(), QImage::Format_ARGB32_Premultiplied );
	QPainter prefl(&mask);
	prefl.fillRect(img.rect(),g);
	prefl.end();

	QImage refl = img.mirrored();
	refl.setAlphaChannel(mask);

	return refl;
}

QImage ImageFxFactory::createBlur(const QImage& image, const QRect& rect, int radius, bool alphaOnly)
{
	int tab[] = { 14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2 };
	int alpha = (radius < 1) ? 16 : (radius > 17) ? 1 : tab[radius-1];

	QImage result = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
	int r1 = rect.top();
	int r2 = rect.bottom();
	int c1 = rect.left();
	int c2 = rect.right();

	int bpl = result.bytesPerLine();
	int rgba[4];
	unsigned char* p;

	int i1 = 0;
	int i2 = 3;

	if (alphaOnly)
		i1 = i2 = (QSysInfo::ByteOrder == QSysInfo::BigEndian ? 0 : 3);

	for (int col = c1; col <= c2; col++) {
		p = result.scanLine(r1) + col * 4;
		for (int i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p += bpl;
		for (int j = r1; j < r2; j++, p += bpl)
			for (int i = i1; i <= i2; i++)
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	for (int row = r1; row <= r2; row++) {
		p = result.scanLine(row) + c1 * 4;
		for (int i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p += 4;
		for (int j = c1; j < c2; j++, p += 4)
			for (int i = i1; i <= i2; i++)
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	for (int col = c1; col <= c2; col++) {
		p = result.scanLine(r2) + col * 4;
		for (int i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p -= bpl;
		for (int j = r1; j < r2; j++, p -= bpl)
			for (int i = i1; i <= i2; i++)
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	for (int row = r1; row <= r2; row++) {
		p = result.scanLine(row) + c2 * 4;
		for (int i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p -= 4;
		for (int j = c1; j < c2; j++, p -= 4)
			for (int i = i1; i <= i2; i++)
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	return result;
}


QImage ImageFxFactory::createDistortionV(const QImage & image,
								qreal freq,
								qreal amp
								)
{
	int h= image.height();
	int w = image.width();

	QImage distorted = QImage(	w + 2*((int)amp+1),
						h,
						QImage::Format_ARGB32_Premultiplied);

	// clear image (transparent)
	distorted.fill( qRgba(0,0,0,0) );
	qreal radfreq = TO_RAD*freq;
	qreal s = .0f;
	for(int y=0; y<h; ++y)
	{
		QRgb * line = (QRgb*)image.scanLine(y);
		s = qSin( (y%360)*radfreq )*amp;
		for(int x=0; x<w; ++x)
		{
			distorted.setPixel(((int)amp+1)+x+s,y,line[x]);
		}
	}

	return distorted;
}

QImage ImageFxFactory::createDistortionH(const QImage & image,
								qreal freq,
								qreal amp
								)
{
	int h= image.height();
	int w = image.width();

	QImage distorted = QImage(	w,
						h+ 2*((int)amp+1),
						QImage::Format_ARGB32_Premultiplied);

	// clear image (transparent)
	distorted.fill( qRgba(0,0,0,0) );
	qreal radfreq = TO_RAD*freq;
	qreal s = .0f;
	for(int x=0; x<w; ++x)
	{
		s = qSin( (x%360)*radfreq )*amp;
		for(int y=0; y<h; ++y)
		{
			distorted.setPixel(x,
							   ((int)amp+1)+y+s,
							   image.pixel(x,y)
							   );
		}
	}

	return distorted;
}
