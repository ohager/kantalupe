#include "ImageListWidget.h"
#include "ImageItem.h"
#include "global.h"
#include "Application.h"


#include "Overlay.h"
#include <QCache>

#include <QtGui>

START_NS

const int IdRole = Qt::UserRole + 0x123;

ImageListWidget::ImageListWidget(int maxi ,QWidget * p)
	: QListWidget(p),
		mOverlay(new Overlay(this)),
		mIsDropAccepted (false),
		_clickedItem(0x0),
		mMaxItems(maxi),
		mIsLabelingEnabled(true),
		mImageItem(0x0)
{
	setupUi();
}

void ImageListWidget::setupUi()
{

	setViewMode(QListView::IconMode);
	setIconSize(QSize(48, 48));
	//setUniformItemSizes(true);
	setMovement(QListView::Static);
	setFixedHeight(90);
	setSpacing(8);
	setWrapping(false);
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
	viewport()->setAcceptDrops(true);
	setDropIndicatorShown(true);
	setDragDropMode(QAbstractItemView::DropOnly);

	QPixmap pixmap;
	if(	!QPixmapCache::find(global::R.getValue("icon/noimage"), pixmap) )
	{
		pixmap.load( global::R.getValue("icon/noimage") );
		pixmap = pixmap.scaled( iconSize(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
		QPixmapCache::insert( pixmap );
	}
	overlay()->setPixmap(pixmap);

	connect(this, SIGNAL(currentRowChanged(int)), this,SLOT(showImage(int)));

/*
	connect(model(), SIGNAL(rowsInserted(const QModelIndex &, int, int)),
			this, SIGNAL(contentChanged()));
	connect(model(), SIGNAL(rowsRemoved(const QModelIndex &, int, int)),
			this, SIGNAL(contentChanged()));
*/

}

void ImageListWidget::removeAllImages()
{
	clear();
	overlay()->show();
	emit contentChanged();
}

void ImageListWidget::removeImage(QListWidgetItem * image)
{
	model()->removeRow( row(image) );
	if(count()==0)
		overlay()->show();

	contentChanged();
}

void  ImageListWidget::addImage(const QString & filename )
{

	int nitems = count();

	if(mMaxItems && nitems==mMaxItems)
	{
		qDebug("ImageListWidget: Maximum Item capacity reached.");
		return;
	}

	for(int r=0; r<nitems; ++r)
	{
		const QListWidgetItem * i = item(r);
		if( i->data(IdRole).toString() == filename )
		{
			qDebug("Item already added");
			return;
		}
	}

	QListWidgetItem * item = new QListWidgetItem(this);
	item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);

	// scale and center the thumbnail for uniform sizes
	const QSize & is = iconSize();
	QImage fimg(filename);
	item->setToolTip(tr("File: %1\nSize: %2 x %3 px")
					 .arg(QFileInfo(filename).fileName())
					 .arg(fimg.width()).arg(fimg.height()) );
	fimg = fimg.scaled(is, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	QImage nimg(is, QImage::Format_ARGB32_Premultiplied);
	QPainter p(&nimg);
	p.setCompositionMode(QPainter::CompositionMode_SourceOver);
	p.fillRect(0,0,is.width(),is.height(), Qt::white );
	if(fimg.width() == fimg.height())
	{
		p.drawImage(0,0,fimg);
	}
	else if (fimg.width() > fimg.height())
	{
		p.drawImage( 0, (is.height() - fimg.height())/2 , fimg);
	}
	else if (fimg.width() < fimg.height())
	{
		p.drawImage( (is.width() - fimg.width())/2 ,0, fimg);
	}
	p.end();

	item->setIcon( QPixmap::fromImage(nimg) );
	if(mIsLabelingEnabled)
	{
		item->setText( tr("Image %1").arg( count() ) );
	}
	item->setData( IdRole , filename );
	qDebug("Image data %s", filename.toAscii().data() );
	addItem(item);
	//emit imageAdded(count()-1);


	overlay()->hide();
	contentChanged();
}


QString ImageListWidget::imageUrl(const QListWidgetItem * image) const
{
	Q_ASSERT_X(image,"ImageListWidget::imageUrl","NULL image");

	return image->data(IdRole).toString();
}


bool ImageListWidget::isAcceptingMime(const QMimeData * mime) const
{
	if(mime->hasUrls())
	{
		// check if at least one image is inside url list
		QList<QUrl> urls = mime->urls();
		int n= urls.size();
		for(int i =0; i<n;++i)
		{

			QString surl =  urls.at(i).toString().toLower();
			qDebug("%u. %s", i, surl.toAscii().data());
			if(surl.startsWith("file:") &&
				(	surl.endsWith(".png") ||
					surl.endsWith(".jpg") )
				)
			{
				return true;
			}
		}
	}
	return false;
}


// ---------------------------------- SLOTS ---------------------------------

void ImageListWidget::onActionRemoveImage()
{

	removeImage( _clickedItem );
}

void ImageListWidget::onActionAddImage()
{
	QStringList files = QFileDialog::getOpenFileNames(this, tr("Select image(s)"), QString("."),
								  tr("Images (*.png *.jpg)")  );
	foreach(QString file, files)
	{
		addImage(file);
	}
}

void ImageListWidget::showImage(int index)
{
	QListWidgetItem * img = item(index);
	if(!img)
	{
		qDebug("showImage() failed: Null image");
		return;
	}

	QPixmap pixmap(img->data(IdRole).toString());
	ImageItem * item= new ImageItem(pixmap,  window());

	connect(item, SIGNAL(fadedOut()), item, SLOT(deleteLater()));
	connect(this, SIGNAL(currentRowChanged(int)), item, SLOT(fadeOut()));
	connect(this, SIGNAL(escapePressed()), item, SLOT(fadeOut()));
	/*
	QString infotext= tr("File: %1\nSize: %2 x %3").arg(img->data(IdRole).toString())
					  .arg(pixmap.width()).arg(pixmap.height());
	item->setInfoText(infotext);
	*/
	item->fadeIn();
}

// ----------------------------------- EVENTS ---------------------------------

/*
void ImageListWidget::mousePressEvent(QMouseEvent *e)
{

	if(e->buttons().testFlag(Qt::LeftButton) )
	{
		QModelIndex index = indexAt(e->pos());
		if(!index.isValid())
		{
			e->ignore();
		}
		else
		{
			showImage(index.row());
			e->accept();
		}
	}

}
*/

void ImageListWidget::keyPressEvent(QKeyEvent * e)
{
	if(e->key() == Qt::Key_Escape)
	{
		emit escapePressed();
	}
	else
	{
		QListWidget::keyPressEvent(e);
	}
}




void ImageListWidget::contextMenuEvent(QContextMenuEvent * e)
{
	_clickedItem = itemAt(e->pos());

	QMenu menu;
	menu.addAction(tr("Add Image..."),this, SLOT(onActionAddImage()));

	if(_clickedItem)
	{

		menu.addAction(tr("Remove Image"),this, SLOT(onActionRemoveImage()));

	}
	menu.addAction(tr("Clear"),this, SLOT(removeAllImages()));

	menu.exec(mapToGlobal(e->pos()));
}

void ImageListWidget::dragEnterEvent(QDragEnterEvent * e)
{
	e->ignore();
	// caching result on enter to avoid 'costly' accept checks on dragMovement
	mIsDropAccepted = isAcceptingMime(e->mimeData());
	if(mIsDropAccepted)
	{
		e->acceptProposedAction();
	}
}


void ImageListWidget::dragMoveEvent(QDragMoveEvent * e)
{
	e->ignore();
	if(mIsDropAccepted)
	{
		e->acceptProposedAction();
	}
}


Qt::DropActions ImageListWidget::supportedDropActions () const
{
	return Qt::CopyAction;
}


void ImageListWidget::dropEvent(QDropEvent * e)
{

	// implicitely accepted!
	qDebug("Dropping...");

	QList<QUrl> urls =e->mimeData()->urls();
	int n= urls.size();
	for(int i =0; i<n;++i)
	{
		QString surl =  urls.at(i).toString().toLower();

		if(!surl.startsWith("file:///")) // currently only local files are accepted
			continue;

		if(surl.endsWith(".png") ||
		   surl.endsWith(".jpg")
		   )
		{
			surl.remove(0,8); // remove 'file:///'
			if( QFile::exists(surl) )
				addImage(surl);
			else
				qDebug("File not exist '%s'", surl.toAscii().data());

		}
	}
	mIsDropAccepted = false; // reset
}



void ImageListWidget::showEvent(QShowEvent *)
{
	overlay()->center();
}

void ImageListWidget::resizeEvent(QResizeEvent *)
{
	overlay()->center();
}

void ImageListWidget::moveEvent(QMoveEvent *)
{
	overlay()->center();
}


END_NS
