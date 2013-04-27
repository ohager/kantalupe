#ifndef SCRIPT_H
#define SCRIPT_H

#include <QString>
#include <QDate>

namespace k{

/**
	Script plain data class. Additionally, to the pure ECMA-262 code, meta information are provided.
	@author O. Haeger
  */
struct Script
{
	Script() : apilevel(0) {}
	/**
	  Checks, whether the data is complete, or not.
	  @return @e true, if all necessary information is available.
	  */
	bool isComplete() const
	{
		return apilevel>0 &&
				!(program.isEmpty() ||
				name.isEmpty() ||
				description.isEmpty() ||
				author.isEmpty() ||
				version.isEmpty() ||
				lastEdited.isNull()
			);
	}

	int apilevel;
	QString program, ///< the script program itself
			name,
			description,
			author,
			version; ///< version for this script, do not confuse with apilevel
	QDate lastEdited;
};


namespace types{
	typedef QList<Script> ScriptList;
}

} // eons

#endif // SCRIPT_H
