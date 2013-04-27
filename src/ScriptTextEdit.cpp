#include "ScriptTextEdit.h"
#include "ScriptHighlighter.h"
#include "ScriptSyntaxChecker.h"
#include "global.h"

#include <QWidget>
#include <QPainter>

START_NS

class LineNumberArea : public QWidget
{
public:
	LineNumberArea(ScriptTextEdit * editor) : QWidget(editor) {
		_scriptEdit = editor;
	}

	QSize sizeHint() const {
		return QSize(_scriptEdit->lineNumberAreaWidth(), 0);
	}

protected:
	void paintEvent(QPaintEvent *event) {
		_scriptEdit->lineNumberAreaPaintEvent(event);
	}

private:
	ScriptTextEdit * _scriptEdit;
};

// -----------------------------------------

ScriptTextEdit::ScriptTextEdit(QWidget *parent) :
	PlainTextEdit(parent),
	mHighlighter(new ScriptHighlighter(document())),
	mSyntaxChecker( new ScriptSyntaxChecker(this) ),
	mLineNumberArea( new LineNumberArea(this) )
{
	setupUi();
}

ScriptTextEdit::~ScriptTextEdit()
{
}

void ScriptTextEdit::setupUi()
{
	QFont font;
	font.setFamily("courier");
	font.setPointSize(10);
	setFont( font );
	setTabStopWidth(40);

	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth()));
	connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

	updateLineNumberAreaWidth();
}



int ScriptTextEdit::lineNumberAreaWidth()
{
	/*
	int digits = 1;
	int max = qMax(1, blockCount());
	while (max >= 10) {
		max /= 10;
		++digits;
	}

	int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;
*/
	static const int MaxDigits = 3;

	int space = 4 + fontMetrics().width(QLatin1Char('9')) * MaxDigits; // 5 digits width may be enough
	return space;
}

// ----------------------------- SLOTS ---------------------------------------------

void ScriptTextEdit::highlightCurrentLine()
{
	QList<QTextEdit::ExtraSelection> extraSelections;
	QTextEdit::ExtraSelection selection;
	QColor lineColor = QColor(Qt::green).lighter(180);
	selection.format.setBackground(lineColor);
	selection.format.setProperty(QTextFormat::FullWidthSelection, true);
	selection.cursor = textCursor();
	selection.cursor.clearSelection();
	extraSelections.append(selection);

	setExtraSelections(extraSelections); // set completely, deleting old ones
}

void ScriptTextEdit::updateLineNumberAreaWidth()
{
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}



void ScriptTextEdit::updateLineNumberArea(const QRect &rect, int dy)
{
	if (dy)
		mLineNumberArea->scroll(0, dy);
	else
		mLineNumberArea->update(0, rect.y(), mLineNumberArea->width(), rect.height());

	if (rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth();
}

void ScriptTextEdit::addExtraSelection(QTextEdit::ExtraSelection e)
{
	setExtraSelections( extraSelections() << e);
}

void ScriptTextEdit::saveExtraSelections()
{
	mExtraSelections = extraSelections();
}

void ScriptTextEdit::restoreExtraSelections()
{
	setExtraSelections(mExtraSelections);
}



// ------------------------------- EVENTS ------------------------------------------
void ScriptTextEdit::resizeEvent(QResizeEvent * e)
{
	PlainTextEdit::resizeEvent(e);
	QRect cr = contentsRect();
	mLineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void ScriptTextEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
	int lineAreaWidth = mLineNumberArea->width();
	QPainter painter(mLineNumberArea);
	painter.fillRect(event->rect(), Qt::white);

	QPen linepen;
	linepen.setWidth(1);
	linepen.setColor( Qt::lightGray );
	painter.setPen(linepen);
	painter.drawLine(lineAreaWidth-1,0,lineAreaWidth-1,mLineNumberArea->height());


	int currentLine = textCursor().blockNumber();
	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	QFont font=painter.font();
	int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int) blockBoundingRect(block).height();
	while (block.isValid() && top <= event->rect().bottom())
	{
		if (block.isVisible() && bottom >= event->rect().top())
		{
			QString number = QString::number(blockNumber + 1);
			painter.setPen(Qt::darkGray);
			font.setBold(blockNumber==currentLine);
			painter.setFont( font );
			painter.drawText(-2, top, lineAreaWidth, fontMetrics().height(),
							 Qt::AlignRight | Qt::AlignVCenter, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int) blockBoundingRect(block).height();
		++blockNumber;
	}
}


END_NS
