#include "ScriptHighlighter.h"
#include "ScriptHighlighterImpl.h"
#include "global.h"

START_NS


ScriptHighlighter::ScriptHighlighter(QTextDocument * doc) :
	QSyntaxHighlighter(doc), mImpl(new ScriptHighlighterImpl(doc))
{

}

void ScriptHighlighter::highlightBlock(const QString &text)
{
	mImpl->highlightBlock(text);
}


END_NS
