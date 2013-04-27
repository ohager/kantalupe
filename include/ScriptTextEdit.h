#ifndef SCRIPTTEXTEDIT_H
#define SCRIPTTEXTEDIT_H

#include "PlainTextEdit.h"

namespace k{

class ScriptHighlighter;
class ScriptSyntaxChecker;
class LineNumberArea;

class ScriptTextEdit : public PlainTextEdit
{
    Q_OBJECT
friend class LineNumberArea;
public:
	explicit ScriptTextEdit(QWidget *parent = 0);
	~ScriptTextEdit();

	void addExtraSelection(QTextEdit::ExtraSelection e);
	void saveExtraSelections();
	void restoreExtraSelections();

protected:
	int lineNumberAreaWidth();
	void resizeEvent(QResizeEvent *);
	void lineNumberAreaPaintEvent(QPaintEvent *);
protected slots:
	void highlightCurrentLine();
	void updateLineNumberAreaWidth();
	void updateLineNumberArea(const QRect &rect, int dy);

private:
	void setupUi();
	ScriptHighlighter * mHighlighter;
	ScriptSyntaxChecker * mSyntaxChecker;
	LineNumberArea * mLineNumberArea;
	QList<QTextEdit::ExtraSelection> mExtraSelections;

};

}

#endif // SCRIPTTEXTEDITOR_H
