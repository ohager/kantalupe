#ifndef DRAG_H
#define DRAG_H

#include <QDrag>

namespace k{

	class Drag : public QDrag
	{
	public:
		Drag ( QWidget * dragSource );
		~Drag();
		Qt::DropAction exec ( Qt::DropActions supportedActions = Qt::MoveAction );
		Qt::DropAction exec ( Qt::DropActions supportedActions, Qt::DropAction defaultDropAction );
	};

} // eons

#endif // DRAG_H
