#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QWidget>
#include <QPixmap>

namespace k{



/**
  A specialize image item with animation effects.
  @author O. Haeger
  @todo More animations
  */
class ImageItem : public QWidget
{
    Q_OBJECT
	Q_PROPERTY(int fade READ fade WRITE setFade)
	Q_PROPERTY(const QString & infotext READ infoText WRITE setInfoText)
signals:
	void fadedIn();
	void fadedOut();
public:
	explicit ImageItem(const QPixmap & img, QWidget * parent = 0);
	explicit ImageItem(const QPixmap & img,const QString & infotext=QString(), QWidget * parent = 0);
	~ImageItem();
	/**
	  Sets a single fade value
	  @param f A value between 0 (transparent) to 255 (opaque)
	  @see fade()
	  */
	void setFade(int f);
	int fade() const;

	/**
	  Sets an additional Infotext that is shown with the image
	  @param text The information text.
	  */
	void setInfoText(const QString & text);
	const QString & infoText() const;

public slots:
	void center();
	void fadeIn();
	void fadeOut();

protected:
	void moveEvent(QMoveEvent *);
	void showEvent(QShowEvent *);
	void resizeEvent(QResizeEvent *);
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *e);


private slots:
	void animationFinished();


private:
	int mFade;
	bool mIsAnimationFinished;
	QString mInfoText;
	QPixmap mPixmapOrig, mPixmap;

};


} // eons

#endif // IMAGEITEM_H
