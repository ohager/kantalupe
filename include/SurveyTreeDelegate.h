#ifndef SurveyTreeDelegate_H
#define SurveyTreeDelegate_H


#include <QStyledItemDelegate>
#include <QHash>
#include "TreeItemProtocol.h"

namespace k{

/**
  This delegate paints an indicator on possible drop targets.
  @author O.Haeger
  */
class SurveyTreeDelegate : public QStyledItemDelegate
{
public:
	SurveyTreeDelegate( QObject  * parent =0);


	void markItemType(tip::ItemType type, bool marked=true);
	void unmarkAllItemTypes();
	void paint( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
private:

	bool mMarkMask[10];
	/*
	QHash<tip::ItemType, bool> mMarkMask;
	*/
};

} // eons

#endif
