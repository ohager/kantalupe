#ifndef WRITEPOLICYXMLIMPL_V1_H
#define WRITEPOLICYXMLIMPL_V1_H

#include <QXmlStreamWriter>
#include "AbstractTreeModelVisitor.h"
#include "ProtocolTypes.h"

class QIODevice;

namespace k{

class AbstractTreeModel;
class TreeItem;

/**
  Xml write implementation. Privta use only.
  @author O. Haeger
  */
class WritePolicyXmlImpl_V1 : public AbstractTreeModelVisitor
{
public:
	WritePolicyXmlImpl_V1();

	static const char * Version;
	bool write(AbstractTreeModel * mtd, QIODevice * out);
	bool write(TreeItem * startnode, QIODevice *out);

	AbstractTreeModelVisitor::TraversalType visit(TreeItem *item);
	void leave(TreeItem *item);

	void writeItem(const Model &);
	void writeItem(const Survey &);
	void writeItem(const Category &);
	void writeItem(const Group &);
	void writeItem(const Matrix &);
	void writeItem(const MatrixProblem &);
	void writeItem(const Problem &);


	void writeProperties(const types::Properties & props);
	void writeSolutions(const types::Solutions & sols);
	void writeProposals(const types::Proposals & props);
	void writeImages(const types::Images & imgs);
	void writeAffiliation(const Affiliation & aff);
	void writeSurveyTexts(const SurveyTexts & texts);


	bool mHasError;
	QXmlStreamWriter mWriter;

};

} // eons

#endif // WRITEPOLICYXMLIMPL_H
