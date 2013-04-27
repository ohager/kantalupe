#ifndef PROTOCOLTYPES_H
#define PROTOCOLTYPES_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QHash>

namespace k{

// ---------------- Model Item data components ---------------------

struct Property {
	QString key, value, description;
};

struct Proposal {
	QString id, text;
};

struct Affiliation
{
	QString firstname,
			lastname,
			email,
			telephone;
};

struct SurveyTexts
{
	QString welcome,
			thank,
			remind;
};

// meta information about the items themselves... like states, etc.
struct Meta{
	Meta() : collapsed(false) {}
	bool collapsed;
};

namespace types{
typedef QHash<QString,Property> Properties; ///< (id,data)
typedef QList<Proposal> Proposals; // order is needed
typedef QStringList Images;
typedef QStringList Solutions;
}


// ------------------ base components (not for public use) --------------------



struct __property
{
	types::Properties properties;
};

struct __image
{
	types::Images images;
};

struct __proposal
{
	bool isMultipleChoice;
	types::Proposals proposals;
};


struct __solution
{
	types::Solutions solutions;
};

// -------------------------- Model item components ---------------------------

struct Model : Meta
{
	enum UidMode{
		UidManual=0,
		UidHash
		// extend here
	};

	QString name;

	// functional parts
	UidMode uidMode;
};

struct Survey : Meta, __property
{
	QString name,
			lastmodifieddate;
	SurveyTexts texts;
	Affiliation affiliation;
	// can be extended
};


struct Category : Meta, __property
{
	QString name;
	QString description;
};

struct Group : Category
{
};

struct Matrix : Meta, __proposal, __property, __image
{
	QString name, text, hint;

};

struct MatrixProblem : Meta,  __property, __solution
{
	QString uid, text;
};


struct Problem : MatrixProblem, __proposal, __image
{
	QString hint;
};


} // eons

#endif // PROTOCOLTYPES_H
