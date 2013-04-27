#ifndef MODELTREEDATAITEMEXTRACTOR_H
#define MODELTREEDATAITEMEXTRACTOR_H

#include "global.h"

class QByteArray;

namespace k{

class ModelTreeDataItem;
class Category;
class Group;
class Matrix;
class MatrixProblem;
class Problem;



/**
  The extractor class 'extracts' plain data structures from ModelTreeDataItem.
  @see ModelTreeDataItemInceptor
  @author O. Haeger
  */
class ModelTreeDataItemExtractor
{
public:
	/**
	  Extracts the data from ModelTreeDataItem to a Category (Group,Matrix,etc...)-object.
	  If failed, destination object remains unchanged and @e false is returned.
	  @param src The data item
	  @param dest The category(or other type) instance, where the data from @e src shall be extracted
	  @return @e true, on successful extraction, otherwise @e false, i.e. @e src does not hold appropriate data.
	  */
	static bool extract(const ModelTreeDataItem * src, Category & dest );
	static bool extract(const ModelTreeDataItem * src, Group & dest );
	static bool extract(const ModelTreeDataItem * src, Matrix & dest );
	static bool extract(const ModelTreeDataItem * src, Problem & dest );
	static bool extract(const ModelTreeDataItem * src, MatrixProblem & dest );

private:
	/**
	  Deserializes the property data stream to its original container
	  @param sprops The serialized property data
	  @return The property container
	  @see ModelTreeDataItemInceptor::serializeProperties()
	  */
	static types::Properties deserializeProperties(const QByteArray & sprops);

	/**
	  Deserializes the solution data stream to its original container
	  @param sols The serialized solution data
	  @return The solution container
	  @see ModelTreeDataItemInceptor::serializeSolutions()
	  */
	static types::Solutions deserializeSolutions(const QByteArray & sols);

	/**
	  Deserializes the proposal data stream to its original container
	  @param sprops The serialized proposal data
	  @return The proposal container
	  @see ModelTreeDataItemInceptor::serializeProposals()
	  */
	static types::Proposals deserializeProposals(const QByteArray & sprops);

	/**
	  Deserializes the image data stream to its original container
	  @param simages The serialized image data
	  @return The image container
	  @see ModelTreeDataItemInceptor::serializeImages()
	  */
	static types::Images deserializeImages(const QByteArray & simages);


    ModelTreeDataItemExtractor();
};

}

#endif // MODELTREEDATAITEMEXTRACTOR_H
