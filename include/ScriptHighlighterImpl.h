#ifndef SCRIPTHIGHLIGHTERIMPL_H
#define SCRIPTHIGHLIGHTERIMPL_H

#include "thirdparty/qscripthighlighter_p.h"

namespace k{


/**
Script highlighter implementation.
Currently, this implementation uses the internal highlighter from
Nokia Qt Designer. This module underlies the rights of LGPL V2.1
and Nokias granted Nokia Qt LGPL Exception version 1.1.

@par Nokia Qt LGPL Exception version 1.1

As an additional permission to the GNU Lesser General Public License version
2.1, the object code form of a "work that uses the Library" may incorporate
material from a header file that is part of the Library.  You may distribute
such object code under terms of your choice, provided that:
	(i)   the header files of the Library have not been modified; and
	(ii)  the incorporated material is limited to numerical parameters, data
		  structure layouts, accessors, macros, inline functions and
		  templates; and
	(iii) you comply with the terms of Section 6 of the GNU Lesser General
		  Public License version 2.1.

Moreover, you may apply this exception to a modified version of the Library,
provided that such modification does not involve copying material from the
Library into the modified Library's header files unless such material is
limited to (i) numerical parameters; (ii) data structure layouts;
(iii) accessors; and (iv) small macros, templates and inline functions of
five lines or less in length.

Furthermore, you are not required to apply this additional permission to a
modified version of the Library.

@author O. Haeger
  */
class ScriptHighlighterImpl
{
public:
	ScriptHighlighterImpl(QTextDocument * doc);
	 ~ScriptHighlighterImpl();
	void highlightBlock(const QString &text);
private:
	qdesigner_internal::QScriptHighlighter * mHighlighter;
};


} // eons

#endif // SCRIPTHIGHLIGHTERIMPL_H
