#ifndef IMAGELISTWIDGET_H
#define IMAGELISTWIDGET_H

#include <QListWidget>


namespace k {

class Overlay;
class ImageItem;

/**
  A list widget especially for images with some additional features, like larg preview.

  */
class ImageListWidget : public QListWidget
{
    Q_OBJECT
signals:
	void contentChanged();
	void escapePressed();
public:
	/**
	  @param maxitems If not 0, the maximum amount of items for this widget is limited
	  @param parent The parent widget
	  */
	explicit ImageListWidget(int maxitems = 0, QWidget * parent = 0);

	bool isAcceptingMime(const QMimeData * mime) const;

	/**
	  Adds an image, if widget'S item limit is not exceeded, or image is not already added.
	  Failures will be omitted silently.
	  @param imageurl The url of the image
	  @see removeImage()
	  */
	void addImage(const QString & imageurl);
	void removeImage(QListWidgetItem * image);
	/**
	  @return The image url from an image item.
	  */
	QString imageUrl(const QListWidgetItem * image) const;

	/**
	  Sets image labeling on or off. It is enabled per default
	  @param enable If @e true, the images will have a label.
	  @todo When changed while images were already added, labeling must be updated either.
	  */
	void setImageLabelingEnabled(bool enable) { mIsLabelingEnabled = enable; }
	inline bool isImageLabelingEnabled() const { return mIsLabelingEnabled; }

	/**
	  @return The maximum allowed item count.
	  */
	inline int maximumItemCount() const { return mMaxItems; }

public slots:
	/**
	  Shows the image in its original size
	  @param index The index of image that shall be shown.
	  */
	void showImage(int index);
	void removeAllImages();

protected slots:
	void onActionRemoveImage();
	void onActionAddImage();


protected:
	void setupUi();
	inline Overlay * overlay() { return mOverlay; }

	//void mousePressEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void contextMenuEvent(QContextMenuEvent *);
	void showEvent(QShowEvent *);
	void resizeEvent(QResizeEvent *);
	void moveEvent(QMoveEvent *);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent * e);
	void dropEvent(QDropEvent *event);

	Qt::DropActions supportedDropActions () const;
private:
	Overlay * mOverlay;
	int mMaxItems;
	bool mIsDropAccepted, mIsLabelingEnabled;
	QListWidgetItem * _clickedItem;
	ImageItem * mImageItem;


};

} // eons

#endif // IMAGELISTWIDGET_H
