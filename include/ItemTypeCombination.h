#ifndef ITEMTYPECOMBINATION_H
#define ITEMTYPECOMBINATION_H

#include <QList>
#include <TreeItemProtocol.h>

namespace k{


struct ItemTypeCombination{
	explicit ItemTypeCombination(tip::ItemType s_, tip::ItemType t_) : s(s_), t(t_) {}
	tip::ItemType s, t;
	bool operator==(const ItemTypeCombination & rhs) const { return rhs.s == s && rhs.t == t;}
	bool operator!=(const ItemTypeCombination & rhs) const { return !operator==(rhs); }
};

/**
  A class to decide if item type combinations are allowed.
  Theis is merely a private class for some internal checkings, i.e. type checks between ModelTree and SurveyTree
  @author O. Haeger
  */
class AllowedItemTypeCombinations : public QList<ItemTypeCombination>
{

public:
	AllowedItemTypeCombinations()
	{
		//push_back( ItemTypeCombination(tip::ItemModel, tip::ItemSurvey) );
		push_back( ItemTypeCombination(tip::ItemCategory, tip::ItemModel) );
		push_back( ItemTypeCombination(tip::ItemCategory, tip::ItemSurvey) );
		push_back( ItemTypeCombination(tip::ItemCategory, tip::ItemCategory) );
		push_back( ItemTypeCombination(tip::ItemGroup, tip::ItemCategory) );
		//push_back( ItemTypeCombination(tip::ItemMatrix, tip::ItemCategory) );
		push_back( ItemTypeCombination(tip::ItemMatrix, tip::ItemGroup) );
		push_back( ItemTypeCombination(tip::ItemMatrixProblem, tip::ItemMatrix) );
		//push_back( ItemTypeCombination(tip::ItemProblem, tip::ItemCategory) );
		push_back( ItemTypeCombination(tip::ItemProblem, tip::ItemGroup) );
	}

	/**
	  @return @e true, if passed type combination is considered "allowed"
	  */
	bool accept(const ItemTypeCombination & c) { return contains(c); }
	bool accept(tip::ItemType source, tip::ItemType target) { return accept(ItemTypeCombination(source, target)); }
};

} // eons


#endif // ITEMTYPECOMBINATION_H
