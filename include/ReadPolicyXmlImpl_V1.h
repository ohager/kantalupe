#ifndef READPOLICYXMLIMPL_V1_H
#define READPOLICYXMLIMPL_V1_H

#include <QModelIndex>
#include <QXmlStreamReader>
#include <QStack>
#include "ProtocolTypes.h"

class QIODevice;
class QModelIndex;

namespace k{

class ModelInsertionInterface;

class ReadPolicyXmlImpl_V1
{
public:
	static const char * Version;
	static const char * TagKModel;
	static const char * TagKSurvey;
	static const char * TagCategory;
	static const char * TagGroup;
	static const char *	TagMatrix;
	static const char *	TagMatrixProblem;
	static const char * TagProblem;
	static const char * TagAffiliation;

	ReadPolicyXmlImpl_V1();
	bool read(QIODevice * out, ModelInsertionInterface * mtd, const QModelIndex & parent);
private:
	// callbacks
	void elementClose(QStringRef tagname);
	void elementOpen(QStringRef tagname);

	void nextElement();
	QModelIndex parentIndex() const;
	//- stackable elements
	QModelIndex readModel();
	QModelIndex readSurvey();
	QModelIndex readCategory();
	QModelIndex readGroup();
	QModelIndex readMatrix();
	//- non-stackables
	void readMatrixProblem();
	void readProblem();

	//- helper
	void readProperties(types::Properties & p);
	void readProposals(types::Proposals & p);
	void readImages(types::Images & i);
	void readSolutions(types::Solutions & s);
	void readAffiliation(k::Affiliation & a);
	void readSurveyMeta(k::SurveyTexts & st);


	ModelInsertionInterface * mModel;
	QXmlStreamReader mReader;
	QStack<QModelIndex> mIndexStack;
};

}
#endif // READPOLICYXMLIMPL_V1_H
