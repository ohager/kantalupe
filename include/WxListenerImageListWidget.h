#ifndef WXLISTENERIMAGELISTWIDGET_H
#define WXLISTENERIMAGELISTWIDGET_H

#include "WidgetExtension.h"

namespace k{

class WxListenerImageListWidget : public k::WxListenerDefault
{
public:
	bool isAcceptingMime(WidgetExtension * wx, const QMimeData * mime) const;
};

} // eons

#endif // WXLISTENERIMAGELISTWIDGET_H
