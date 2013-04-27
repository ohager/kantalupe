#ifndef TREEITEMPROTOCOL_H
#define TREEITEMPROTOCOL_H

#include <qt> // for Qt::UserRole
#include "ProtocolTypes.h"


namespace k{

class TreeItem;
/**
  The data carrier protocol for ModelTreeDataItem objects and their
  plain data structure counterpart. This is for loose coupling,
  where ModelTreeDataItem needs to be exchanged.
  @author O. Haeger
  */
class TreeItemProtocol{

public:
	/**
	Types of (model) items
	*/
	enum ItemType{
		ItemUnspecified=200, ///< unspecified item
		ItemModel, ///< model item
		ItemCategory, ///< category item
		ItemGroup, ///< Group item
		ItemMatrix, ///< Matrix item
		ItemMatrixProblem, ///< Matrix Problem item
		ItemProblem, ///< Problem item
		ItemSurvey ///< Survey item

	};

	/**
	  Item data roles for plain data, that are also persistent
	  Usually only for internal usage
	  */
	enum ItemRoles{
		RoleProperties = Qt::UserRole + 0x300,
		RoleImages,
		RoleProposals,
		RoleSolutions,
		RoleMatrixProblems,
		RoleUid,
		RoleUidMode,
		RoleHint,
		RoleMultipleChoice,
		RoleAffiliation,
		RoleTexts,
		RoleDate,
		// extend then
	};

	/**
	  Data roles for meta information, i.e. information
	  need for internal processings, usually transient information
	  */
	enum ItemMetaRoles{
		MetaRoleCollapsed = Qt::UserRole + 0x200
	};

	/**
	  Data roles for information used by script processing.
	  */
	enum ItemScriptRoles{
		ScriptRoleSelected = Qt::UserRole + 0x100
	};

	/**
		'Incepts' plain data structures into model item components.
		@param src The src object
		@param dest The model tree item, which will receive a representation of @e src
		@see extract()
	*/
	static void incept(const Category & src, TreeItem * dest);
	static void incept(const Group & src, TreeItem * dest);
	static void incept(const Matrix & src, TreeItem * dest);
	static void incept(const MatrixProblem & src, TreeItem * dest);
	static void incept(const Problem & src, TreeItem * dest);
	static void incept(const Model & src, TreeItem * dest);
	static void incept(const Survey & src, TreeItem * dest);

	/**
	  'Extracts' the data from ModelTreeDataItem to a Category (Group,Matrix,etc...)-object.
	  If failed, destination object remains unchanged and @e false is returned.
	  @param src The data item
	  @param dest The category(or other type) instance, where the data from @e src shall be extracted
	  @return @e true, on successful extraction, otherwise @e false, i.e. @e src does not hold appropriate data.
	  @see incept()
	  */
	static bool extract(const TreeItem * src, Category & dest );
	static bool extract(const TreeItem * src, Group & dest );
	static bool extract(const TreeItem * src, Matrix & dest );
	static bool extract(const TreeItem * src, Problem & dest );
	static bool extract(const TreeItem * src, MatrixProblem & dest );
	static bool extract(const TreeItem * src, Model & dest );
	static bool extract(const TreeItem * src, Survey & dest );


private:


	/**
	  Serializes the data containers
	  @param src The container
	  @param [out] dest The serialized version of @e src
	  @see deserialize()
	  */
	static void serializeProperties(const types::Properties & src, QByteArray & dest);
	static void serializeSolutions(const types::Solutions & src, QByteArray & dest);
	static void serializeProposals(const types::Proposals & src, QByteArray & dest);
	static void serializeImages(const types::Images & src, QByteArray & dest);
	static void serializeAffiliation(const Affiliation & src, QByteArray & dest);
	static void serializeSurveyTexts(const SurveyTexts & src, QByteArray & dest);
	/**
	  Deserializes the data containers
	  @param src The container
	  @param [out] dest The serialized version of @e src
	  @see serialize()
	  */
	static void deserializeProperties(const QByteArray & src, types::Properties & dest);
	static void deserializeSolutions(const QByteArray & src, types::Solutions & dest);
	static void deserializeProposals(const QByteArray & src, types::Proposals & dest);
	static void deserializeImages(const QByteArray & src, types::Images & dest);
	static void deserializeAffiliation(const QByteArray & src, Affiliation & dest);
	static void deserializeSurveyTexts(const QByteArray & src, SurveyTexts & dest);
};

/**
  Use for abbreviation purposes
  */
struct tip : TreeItemProtocol {};

} // eons

#endif // MODELTREEDATAITEMPROTOCOL_H
