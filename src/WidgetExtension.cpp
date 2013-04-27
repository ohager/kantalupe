#include "WidgetExtension.h"
#include "global.h"
#include "UserModeEvent.h"
#include "DragStartedEvent.h"
#include "DragStoppedEvent.h"
#include "Overlay.h"

#include "Application.h"
#include <QtGui>

START_NS

// -------------------- Default Listener Implementation -----------------
bool WxListenerDefault::isAcceptingMime(WidgetExtension * wx, const QMimeData * d) const
{
	Q_UNUSED(wx);
	Q_UNUSED(d);

	return true;

};

void WxListenerDefault::onUserModeChange(WidgetExtension * wx, UserModeEvent * me)
{
	bool visible = false;
	WidgetExtension::Options opts=wx->optionFlags();
	switch(me->userMode())
	{
	case global::UserModeNovice:
		visible = opts.testFlag( WidgetExtension::VisibleInNoviceModeOnly );
		qDebug("WxL: Novice %s", visible ? "on" : "off");
		break;
	case global::UserModeExpert:
		visible = opts.testFlag( WidgetExtension::VisibleInExpertModeOnly );
		qDebug("WxL: Expert %s", visible ? "on" : "off");
		break;
	}

	wx->widget()->setVisible( visible );
	me->accept();

}


void WxListenerDefault::onDragStarted(WidgetExtension * wx, DragStartedEvent * e)
{
	// eventually show dnd-overlay

	qDebug("WX: Drag started event...");
	e->ignore();
	WidgetExtension::Options opts=wx->optionFlags();
	if( opts.testFlag( WidgetExtension::ShowDropIndicator ) &&
		isAcceptingMime(wx, e->mimeData())
	   )
	{
		qDebug("accepting...");
		Overlay * o=wx->dropIndicator();
		QObject::connect( e->mimeData(), SIGNAL(destroyed()),o, SLOT(hide()));
		o->show();
		o->center();
		e->accept();

	}

}

void WxListenerDefault::onDrop(WidgetExtension * wx, QDropEvent * e)
{
	Q_UNUSED(e);

	if(Overlay * o=wx->dropIndicator())
		o->hide();
}

void WxListenerDefault::onDragStopped(WidgetExtension * wx, DragStoppedEvent * e)
{
	Q_UNUSED(e);
	if(Overlay * o=wx->dropIndicator())
		o->hide();
}

// ----------------------------------------------------------------

WidgetExtension::WidgetExtension(QWidget * widget, Options o, QObject * p) :
	QObject(p),
	_widget(widget),
	mListener(0x0),
	mOptFlags(o),
	_dropIndicator(0x0)

{
	kApp->installEventFilter(this);
	setListener( new WxListenerDefault() );
	connect(_widget, SIGNAL(destroyed()), this, SLOT(deleteLater()));
}

WidgetExtension::~WidgetExtension()
{
	qDebug("WidgetExtension: deleting...");
	kApp->removeEventFilter(this);
	delete mListener;
}

void WidgetExtension::setListener(WidgetExtension::Listener * l)
{
	if(mListener)
		delete mListener;
	mListener = l;
}

Overlay * WidgetExtension::dropIndicator()
{
	// lazy creation
	if(!_dropIndicator)
	{
		_dropIndicator = new Overlay(widget());
		QPixmap pm;
		QString file( global::R.getValue("icon/drop") );
		if(!QPixmapCache::find(file,&pm))
		{
			if(!pm.load(file))
			{
				qDebug("Could not load drop indicator: %s", file.toAscii().data());
			}
			else
			{
				pm = pm.scaled(32,32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
				QPixmapCache::insert(file, pm);
			}
		}

		// no image found... so we use text
		if(pm.isNull())
		{
			_dropIndicator->setText(tr("Drop here"));
		}
		else
		{
			_dropIndicator->setPixmap(pm);
		}

		_dropIndicator->hide();
	}
	return _dropIndicator;
}


bool WidgetExtension::eventFilter(QObject * obj, QEvent * e)
{
	Q_UNUSED(obj);

	bool consume = false;
	if(mListener)
	{
		QEvent::Type t= e->type();
		if(t == global::UserMode)
		{
			mListener->onUserModeChange(this, static_cast<UserModeEvent*>(e));
		}
		else if( t == global::DragStarted )
		{
			mListener->onDragStarted(this, static_cast<DragStartedEvent*>(e));
		}
		else if( t == global::DragStopped )
		{
			mListener->onDragStopped(this, static_cast<DragStoppedEvent*>(e));
		}
		else if (t == QEvent::Drop )
		{
			mListener->onDrop(this, static_cast<QDropEvent*>(e));
		}
	}



	return consume;
}


END_NS

