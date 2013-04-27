#ifndef CONTENTFRAME_H
#define CONTENTFRAME_H

#include "Widget.h"


namespace k{

class ContentFrame 	: public Widget
{
	Q_OBJECT
public:
	ContentFrame(QWidget * parent=0x0);
	~ContentFrame();
	QSize sizeHint () const;
	bool isAcceptingMime(const QMimeData *m) const;

protected:

	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent*);
private:
	QPoint mDragStartPos;
};


} // eons

#endif // CONTENTFRAME_H
