#include "ReadPolicyXmlImpl_V1.h"
#include "ModelInsertionInterface.h"
#include "TreeItem.h"
#include "TreeItemProtocol.h"
#include <QApplication>


#include "global.h"
START_NS



const char * ReadPolicyXmlImpl_V1::Version="1";
const char * ReadPolicyXmlImpl_V1::TagKModel="KModel";
const char * ReadPolicyXmlImpl_V1::TagKSurvey="KSurvey";
const char * ReadPolicyXmlImpl_V1::TagCategory="Category";
const char * ReadPolicyXmlImpl_V1::TagGroup="Group";
const char * ReadPolicyXmlImpl_V1::TagMatrix="Matrix";
const char * ReadPolicyXmlImpl_V1::TagMatrixProblem="MatrixProblem";
const char * ReadPolicyXmlImpl_V1::TagProblem="Problem";



ReadPolicyXmlImpl_V1::ReadPolicyXmlImpl_V1() : mModel(0x0){

}

bool ReadPolicyXmlImpl_V1::read(QIODevice * in, ModelInsertionInterface * mtd, const QModelIndex & parent)
{
	Q_ASSERT(mtd);
	Q_ASSERT(in);

	if(in->isOpen())
		in->close();

	if(!in->open(QIODevice::ReadOnly))
	{
		QString what=QApplication::translate("errmsg","Cannot open IO-Device!");
		MessageHandler::error("ReadPolicyXmlImpl_V1","read", what, in->errorString());
		return false;
	}

	// the start insert node, if given
	if(parent.isValid())
		mIndexStack.push(parent);

	mModel = mtd;
	mReader.setDevice(in);
	while(!mReader.atEnd() && !mReader.hasError())
	{
		mReader.readNext();
		if(mReader.isStartElement())
		{
			elementOpen(mReader.name());
		}
		else if( mReader.isEndElement() )
		{
			elementClose(mReader.name());
		}
	}

	in->close();
	return !mReader.hasError();
}


void ReadPolicyXmlImpl_V1::elementOpen(QStringRef tagname)
{
	if(tagname == TagKModel )
	{
		mIndexStack.push(readModel());
	}
	if(tagname == TagKSurvey)
	{
		mIndexStack.push(readSurvey());
	}
	else if(tagname == TagCategory)
	{
		mIndexStack.push(readCategory());
	}
	else if(tagname == TagGroup)
	{
		mIndexStack.push(readGroup());
	}
	else if(tagname == TagMatrix)
	{
		mIndexStack.push(readMatrix());
	}
	else if(tagname == TagProblem)
	{
		// no stackin on terminate symbols
		readProblem();
	}
	else if(tagname == TagMatrixProblem )
	{
		// no stackin on terminate symbols
		readMatrixProblem();
	}

	qDebug("xml read: <%s>", tagname.toString().toAscii().data());
}


void ReadPolicyXmlImpl_V1::elementClose(QStringRef tagname)
{
	if(tagname == TagKModel ||
		tagname == TagCategory ||
		tagname == TagGroup ||
		tagname == TagMatrix	)
	{
		mIndexStack.pop();
	}

	qDebug("xml read: </%s>", tagname.toString().toAscii().data());
}

void ReadPolicyXmlImpl_V1::nextElement()
{
	bool isopen=false;
	while(!mReader.atEnd() && !mReader.hasError() && !isopen)
	{
		isopen = mReader.readNextStartElement();
	}

}

QModelIndex ReadPolicyXmlImpl_V1::parentIndex() const
{
	return mIndexStack.top();
}

QModelIndex ReadPolicyXmlImpl_V1::readModel()
{
	Model m;
	// KModel atts
	QXmlStreamAttributes atts = mReader.attributes();
	m.name = atts.value("name").toString();

	if(atts.value("version").toString() != Version)
	{
		mReader.raiseError( QApplication::translate("xmlerr",
				"Wrong model version. Received version %1, but #%2 is expected")
						   .arg(atts.value("version").toString())
						   .arg(Version) );
		return QModelIndex();
	}

	nextElement(); // Functional
	nextElement(); // UidGenerator

	if(!mReader.hasError())
	{

		QStringRef uidmode = mReader.attributes().at(0).value();
		if(uidmode=="hash")
		{
			m.uidMode = Model::UidHash;
		}
		else if(uidmode=="manual")
		{
			m.uidMode = Model::UidManual;
		}
		else
		{
			qDebug("Unknown Uid-Mode... set to 'manual'");
			m.uidMode = Model::UidManual;
		}
	}


	nextElement(); // Content
	return mModel->insertNewModel(m)->index();
}

QModelIndex ReadPolicyXmlImpl_V1::readSurvey()
{
	Survey s;
	QXmlStreamAttributes atts = mReader.attributes();

	s.name = atts.value("name").toString();

	if(atts.value("version").toString() != Version)
	{
		mReader.raiseError( QApplication::translate("xmlerr",
				"Wrong model version. Received version %1, but #%2 is expected")
						   .arg(atts.value("version").toString())
						   .arg(Version) );
		return QModelIndex();
	}

	s.lastmodifieddate = atts.value("lastmodified").toString();

	nextElement(); // Meta
	nextElement(); // Affiliation
	readAffiliation(s.affiliation);
	nextElement(); // Welcome
	s.texts.welcome = mReader.readElementText();
	nextElement(); // Thank
	s.texts.thank = mReader.readElementText();
	nextElement(); // Remind
	s.texts.remind = mReader.readElementText();

	return mModel->insertNewSurvey(s)->index();
}

QModelIndex ReadPolicyXmlImpl_V1::readCategory()
{
	Category c;
	c.name = mReader.attributes().value("name").toString();
	nextElement(); // Description
	c.description = mReader.readElementText();

	nextElement(); // PropertyList
	readProperties(c.properties);
	return mModel->insertNewCategory(c, parentIndex())->index();

}

QModelIndex ReadPolicyXmlImpl_V1::readGroup()
{
	Group g;
	g.name = mReader.attributes().value("name").toString();
	nextElement(); // Description
	g.description = mReader.readElementText();
	nextElement(); // PropertyList
	readProperties(g.properties);
	return mModel->insertNewGroup(g, parentIndex())->index();

}

QModelIndex ReadPolicyXmlImpl_V1::readMatrix()
{
	Matrix m;
	QXmlStreamAttributes atts = mReader.attributes();
	m.name = atts.value("name").toString();
	m.isMultipleChoice = atts.value("multi") == "true" ? true : false;
	nextElement(); // PropertyList
	readProperties(m.properties);
	nextElement(); // Text
	m.text = mReader.readElementText();
	nextElement(); // Hint
	m.hint = mReader.readElementText();
	nextElement(); // ImageList
	readImages(m.images);
	nextElement(); // ProposalList
	readProposals(m.proposals);

	return mModel->insertNewMatrix(m, parentIndex())->index();

}

void ReadPolicyXmlImpl_V1::readMatrixProblem()
{
	MatrixProblem p;
	QXmlStreamAttributes atts = mReader.attributes();
	p.uid = atts.value("uid").toString();
	nextElement(); // PropertyList
	readProperties(p.properties);
	nextElement(); // Text
	p.text = mReader.readElementText();
	nextElement(); // SolutionList
	readSolutions(p.solutions);

	mModel->insertNewMatrixProblem(p, parentIndex());
}

void ReadPolicyXmlImpl_V1::readProblem()
{
	Problem p;
	QXmlStreamAttributes atts = mReader.attributes();
	p.uid = atts.value("uid").toString();
	p.isMultipleChoice = atts.value("multiple") == "true" ? true : false;
	nextElement(); // PropertyList
	readProperties(p.properties);
	nextElement(); // Text
	p.text = mReader.readElementText();
	nextElement(); // Hint
	p.hint = mReader.readElementText();
	nextElement(); // ImageList
	readImages(p.images);
	nextElement(); // ProposalList
	readProposals(p.proposals);
	nextElement(); // SolutionList
	readSolutions(p.solutions);

	mModel->insertNewProblem(p, parentIndex());
}

 // -----------------------------------------------------------------
void ReadPolicyXmlImpl_V1::readAffiliation(Affiliation & aff)
{
	nextElement(); // FirstName
	aff.firstname = mReader.readElementText();

	nextElement(); // LastName
	aff.lastname = mReader.readElementText();

	nextElement(); // EMail
	aff.email = mReader.readElementText();

	nextElement(); // Phone
	aff.telephone = mReader.readElementText();

}


void ReadPolicyXmlImpl_V1::readProperties(types::Properties & props)
{
	Property p;
	QStringRef elname;
	QXmlStreamReader::TokenType type;
	forever{
		type = mReader.readNext();
		if(type == QXmlStreamReader::StartElement)
		{
			elname = mReader.name();
			if(elname=="Property")
			{
				QXmlStreamAttributes atts = mReader.attributes();
				p.key = atts.value("key").toString();
				p.value = atts.value("value").toString();
				p.description = mReader.readElementText();
				props.insert(p.key, p);
			}
		}
		else if(type == QXmlStreamReader::EndElement)
		{
			elname = mReader.name();
			if(elname != "Property")
				break;
		}
	}
}

void ReadPolicyXmlImpl_V1::readProposals(types::Proposals & props)
{

	Proposal p;	
	QStringRef elname;
	QXmlStreamReader::TokenType type;
	forever{
		type = mReader.readNext();
		if(type == QXmlStreamReader::StartElement)
		{
			elname = mReader.name();
			if(elname=="Proposal")
			{
				p.id = mReader.attributes().value("id").toString();
				p.text = mReader.readElementText();
				props.append(p);
			}
		}
		else if(type == QXmlStreamReader::EndElement)
		{
			elname = mReader.name();
			if(elname != "Proposal")
				break;
		}
	}
}

void ReadPolicyXmlImpl_V1::readImages(types::Images & imgs)
{
	QStringRef elname;
	QXmlStreamReader::TokenType type;
	forever{
		type = mReader.readNext();
		if(type == QXmlStreamReader::StartElement)
		{
			elname = mReader.name();
			if(elname=="Image")
			{
				imgs.append( mReader.readElementText() ); // string urls
			}
		}
		else if(type == QXmlStreamReader::EndElement)
		{
			elname = mReader.name();
			if(elname != "Image")
				break;
		}
	}

}

void ReadPolicyXmlImpl_V1::readSolutions(types::Solutions & sols)
{
	QStringRef elname;
	QXmlStreamReader::TokenType type;
	forever{
		type = mReader.readNext();
		if(type == QXmlStreamReader::StartElement)
		{
			elname = mReader.name();
			if(elname=="Solution")
			{
				sols.append( mReader.attributes().value("idref").toString() );
			}
		}
		else if(type == QXmlStreamReader::EndElement)
		{
			elname = mReader.name();
			if(elname != "Solution")
				break;
		}
	}

}



END_NS
