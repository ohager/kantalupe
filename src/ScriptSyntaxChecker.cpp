#include "ScriptSyntaxChecker.h"
#include "global.h"
#include <QTextCursor>
#include <QtScript>

#include "SignalBlocker.h"

#include "ScriptTextEdit.h"

START_NS

ScriptSyntaxChecker::ScriptSyntaxChecker(ScriptTextEdit * textedit, QObject *parent) :
	QObject(parent), _textEdit(textedit), mAlreadyAdded(false)
{
	connect(_textEdit,SIGNAL(destroyed()), this, SLOT(__destroyed()));
	connect(_textEdit,SIGNAL(textChanged()), this, SLOT(__delayedSyntaxCheck()));
}




void ScriptSyntaxChecker::checkSyntax()
{

	if(!_textEdit)
	{
		qDebug() << "ScriptSyntaxChecker: document object does not exist anymore";
		return;
	}

	QScriptSyntaxCheckResult result =  QScriptEngine::checkSyntax(_textEdit->toPlainText());


	if(result.state()==QScriptSyntaxCheckResult::Error)
	{

		int line = result.errorLineNumber();

		QTextEdit::ExtraSelection selection;
		selection.cursor = QTextCursor(_textEdit->document());
		selection.cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, line-1);
		//selection.format.setBackground( QColor(255,128,128) );
		selection.format.setProperty( QTextFormat::FullWidthSelection, true);
		selection.format.setProperty( QTextFormat::TextUnderlineStyle, QTextCharFormat::SpellCheckUnderline);
		selection.format.setProperty( QTextFormat::TextUnderlineColor, QColor(255,128,128));

		//_textEdit->saveExtraSelections();
		_textEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>() << selection);
		//mAlreadyAdded = true;
	}


}


// ------------------------------ private slots --------------------------

void ScriptSyntaxChecker::__destroyed(){
	_textEdit = 0x0;
}

void ScriptSyntaxChecker::__delayedSyntaxCheck()
{
	QTimer::singleShot(1000,this, SLOT(checkSyntax()));

}

END_NS
