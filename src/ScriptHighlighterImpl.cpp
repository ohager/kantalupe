#include "ScriptHighlighterImpl.h"
#include "thirdparty/qscripthighlighter_p.h"
#include "global.h"

using namespace qdesigner_internal;

START_NS

ScriptHighlighterImpl::ScriptHighlighterImpl(QTextDocument * doc) :
	mHighlighter( new QScriptHighlighter(doc) )
{
}

void ScriptHighlighterImpl::highlightBlock(const QString &text)
{
	mHighlighter->highlightBlock(text);

	// do our additionalstuff
}

END_NS
