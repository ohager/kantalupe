#include "ModelTreeDelegate.h"
#include "ModelTree.h"
#include "TreeItemProtocol.h"
#include "TreeItem.h"
#include "TreeView.h"

#include "global.h"
#include <QtGui>

START_NS

ModelTreeDelegate::ModelTreeDelegate(QObject * parent)
	: QStyledItemDelegate(parent)
{
}



void ModelTreeDelegate::paint( QPainter * painter,
									const QStyleOptionViewItem & option,
								   const QModelIndex & index ) const
{
	QStyledItemDelegate::paint(painter, option, index);

	const ModelTree * m = qobject_cast<const ModelTree*>(index.model());
	Q_ASSERT(m);
	TreeItem * item = m->itemFromIndexAsTreeItem(index);

	// now we add our stuff
	painter->save();
	painter->setRenderHints( QPainter::Antialiasing | QPainter::TextAntialiasing );




	if(TreeView::isItemCollapsed(index)) // collapse other than Problem-Items
	{
		const QString text("[...]");
		QFont f;
		f.setPixelSize(8);
		f.setItalic(true);

		painter->setFont( f );
		QRectF rect(option.rect);
		rect.adjust(0,0,-8,0);
		painter->drawText(rect, Qt::AlignRight | Qt::AlignVCenter, text );
	}

	// now, paint the solution items
	tip::ItemType type = item->getItemType();
	int iconsize= 12;
	static const int IconSpacing = 2;
	if(type == tip::ItemMatrix)
	{
		Matrix matrix;
		tip::extract(item, matrix);
		if(!matrix.images.isEmpty())
		{
			QPixmap pixmap;
			getImagePixmap(pixmap); // is cached
			item->setIcon( QIcon(pixmap) );
		}
		else
		{
			item->setIcon( QIcon() );
		}
	}

	if(type == tip::ItemMatrixProblem)
	{
		MatrixProblem obj;
		Matrix matrix;
		const TreeItem * matrixitem = (const TreeItem * )item->parent();
		tip::extract(item, obj);
		tip::extract(matrixitem, matrix);

		int nprops = matrix.proposals.size();
		for(int i=0; i<nprops; ++i)
		{
			const Proposal &p = matrix.proposals.at((nprops-1)-i); // reverse iterate
			int x = option.rect.width() - ((i+1)*(iconsize+IconSpacing)) - iconsize/2; // 4 is margin
			int y = option.rect.y() + (option.rect.height() - iconsize)/2;
			/*
			QPixmap pixmap;
			getSolutionPixmap( obj.solutions.contains(p.id),pixmap, iconsize );
			painter->drawPixmap(x, y,  pixmap);
			*/
			paintSolutionIcon(painter,x,y,iconsize, obj.solutions.contains(p.id) );
		}

		if(!nprops)
		{
			const QString text("No proposals yet!");
			QFont f;
			f.setPixelSize(8);
			f.setItalic(true);

			painter->setFont( f );
			QRectF rect(option.rect);
			rect.adjust(0,0,-8,0);
			painter->drawText(rect, Qt::AlignRight | Qt::AlignVCenter, text );
		}

	}
	else if(type == tip::ItemProblem)
	{
		Problem obj;
		tip::extract(item, obj);

		if(!obj.images.isEmpty())
		{
			QPixmap pixmap;
			getImagePixmap(pixmap); // is cached
			item->setIcon( QIcon(pixmap) );
		}
		else
		{
			item->setIcon( QIcon() );
		}

		int nprops = obj.proposals.size();
		for(int i=0; i<nprops; ++i)
		{
			const Proposal &p = obj.proposals.at((nprops-1)-i); // reverse iterate
			int x = option.rect.width() - ((i+1)*(iconsize + IconSpacing)) - iconsize/2;
			int y = option.rect.y() + (option.rect.height() - iconsize)/2;
			/*
			QPixmap pixmap;
			getSolutionPixmap( obj.solutions.contains(p.id),pixmap, iconsize );
			painter->drawPixmap(x, y,  pixmap);
			*/
			paintSolutionIcon(painter,x,y,iconsize, obj.solutions.contains(p.id) );
		}

		if(!nprops)
		{
			const QString text("No proposals yet!");
			QFont f;
			f.setPixelSize(8);
			f.setItalic(true);

			painter->setFont( f );
			QRectF rect(option.rect);
			rect.adjust(0,0,-8,0);
			painter->drawText(rect, Qt::AlignRight | Qt::AlignVCenter, text );
		}
	}




	painter->restore();


}



void ModelTreeDelegate::paintSolutionIcon(QPainter * painter, int x, int y, int size, bool solution) const
{

	painter->drawEllipse(x, y, size,size);

	if(solution)
	{
		static const int InnerOffset=4;
		QBrush b(painter->brush());
		Qt::BrushStyle style = b.style();
		b.setStyle(Qt::SolidPattern);
		painter->setBrush( b );
		painter->drawEllipse(x+InnerOffset/2, y+InnerOffset/2, size-InnerOffset, size-InnerOffset);
		b.setStyle(style);
		painter->setBrush( b );
	}

}


void ModelTreeDelegate::getSolutionPixmap(bool solution, QPixmap & pix, const QSize & itemsize) const
{
	QString icon( solution ?
				  global::R.getValue("icon/correct") :
				  global::R.getValue("icon/false")	  );

	QString iconkey(icon + "_delegate");

	if(!QPixmapCache::find(iconkey,pix) )
	{
		pix = QPixmap(icon).scaled( itemsize,  Qt::KeepAspectRatio,  Qt::SmoothTransformation);
		QPixmapCache::insert(iconkey, pix);
	}
}

void ModelTreeDelegate::getImagePixmap(QPixmap & pix) const
{
	QString icon = global::R.getValue("icon/noimage");
	QString iconkey(icon + "_delegate");
	if(!QPixmapCache::find(iconkey,pix) )
	{
		pix = QPixmap(icon).scaled( QSize(24,24),  Qt::KeepAspectRatio,  Qt::SmoothTransformation);
		QPixmapCache::insert(iconkey, pix);
	}
}

END_NS

