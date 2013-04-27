#ifndef ModelTreeDelegate_H
#define ModelTreeDelegate_H


#include <QStyledItemDelegate>

namespace k{

/**
  This delegate paints an indicator on collapsed items.
  To detect, if an item is collapse or not, request the items
  user data with RoleIsExpanded. This implies, that an item updates
  this state on expand resp. collapse events.
  @author O.Haeger
  */
class ModelTreeDelegate : public QStyledItemDelegate
{
public:
	ModelTreeDelegate( QObject  * parent =0);
	void paint( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
private:
	void paintSolutionIcon(QPainter * p, int x, int y, int size, bool solution) const;
	void getSolutionPixmap(bool issolution, QPixmap & out,const QSize & is) const;
	void getImagePixmap(QPixmap & out) const;
};

} // eons

#endif
