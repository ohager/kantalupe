#ifndef SCRIPTHIGHLIGHTER_H
#define SCRIPTHIGHLIGHTER_H

#include <QSyntaxHighlighter>


namespace k{

class ScriptHighlighterImpl;

class ScriptHighlighter : public QSyntaxHighlighter
{
public:
	ScriptHighlighter(QTextDocument * doc);
	void highlightBlock(const QString &text);
private:
	ScriptHighlighterImpl * mImpl;
};


} // eons

#endif // SCRIPTHIGHLIGHTER_H
