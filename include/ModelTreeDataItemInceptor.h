#ifndef MODELTREEDATAITEMINCEPTOR_H
#define MODELTREEDATAITEMINCEPTOR_H

#include "global.h"

class QString;

namespace k{

class ModelTreeDataItem;
class Category;
class Group;
class Matrix;
class MatrixProblem;
class Problem;

/**
  The inceptor class 'incepts' plain data structures into ModelTreeDataItem.
  @see ModelTreeDataItemExtractor
  @author O. Haeger
  */
class ModelTreeDataItemInceptor
{
public:
	static void incept(const Category & src, ModelTreeDataItem * dest);
	static void incept(const Group & src, ModelTreeDataItem * dest);
	static void incept(const Matrix & src, ModelTreeDataItem * dest);
	static void incept(const MatrixProblem & src, ModelTreeDataItem * dest);
	static void incept(const Problem & src, ModelTreeDataItem * dest);

private:
	/**
	  Serializes the property container
	  @param p The property container
	  @return the serialized data, that can be deserialized with ModelTreeDataItemExtractor::deserialize.
	  */
	static QByteArray serializeProperties(const types::Properties & p);

	/**
	  Serializes the solution container
	  @param s The solution container
	  @return the serialized data, that can be deserialized with ModelTreeDataItemExtractor::deserialize.
	  */
	static QByteArray serializeSolutions(const types::Solutions & s);

	/**
	  Serializes the proposals container
	  @param p The proposals container
	  @return the serialized data, that can be deserialized with ModelTreeDataItemExtractor::deserialize.
	  */
	static QByteArray serializeProposals(const types::Proposals & p);

	/**
	  Serializes the image container
	  @param images The image container
	  @return the serialized data, that can be deserialized with ModelTreeDataItemExtractor::deserialize.
	  */
	static QByteArray serializeImages(const types::Images & images);

    ModelTreeDataItemInceptor();
};

} // eons

#endif // MODELTREEDATAITEMINCEPTOR_H
