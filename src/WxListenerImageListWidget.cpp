#include "WxListenerImageListWidget.h"
#include "ImageListWidget.h"
#include "global.h"

START_NS


bool WxListenerImageListWidget::isAcceptingMime(WidgetExtension * wx, const QMimeData * mime) const
{
	// using the already existing mime acceptor
	ImageListWidget * imglist = (ImageListWidget*)wx->widget();
	return imglist->isAcceptingMime(mime);
}


END_NS
