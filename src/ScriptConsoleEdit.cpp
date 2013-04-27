#include "ScriptConsoleEdit.h"
#include "Overlay.h"
#include "global.h"
#include <QtGui>

START_NS

ScriptConsoleEdit::ScriptConsoleEdit(QWidget * parent ) : PlainTextEdit(parent)
{
	setupUi();
}

void ScriptConsoleEdit::setupUi()
{
	overlay()->setText(tr("Script Console"));
	setReadOnly(true);
	QTextCharFormat format;
	//format.setFontFamily("courier");
	format.setFontPointSize(8);
	format.setForeground( Qt::black );
	setCurrentCharFormat(format);
}


void ScriptConsoleEdit::appendDebugText(const QString & msg)
{
	QTextCharFormat format = currentCharFormat();
	QTextCharFormat debug;
	debug.setForeground( QColor("slategray") );
	setCurrentCharFormat(debug);
	appendPlainText( tr("[Debug] %1").arg(msg) );
	setCurrentCharFormat( format );

}

void ScriptConsoleEdit::appendWarningText(const QString & msg, int line)
{
	QTextCharFormat format = currentCharFormat();
	QTextCharFormat warning;
	warning.setForeground( QColor("darkorange") );
	setCurrentCharFormat(warning);
	QString message;
	if(line!=-1)
	{
		message = tr("[Warning in line %1] %2").arg(line).arg(msg);
	}
	else
	{
		message = tr("[Warning] %1").arg(msg);
	}
	appendPlainText( message );
	setCurrentCharFormat( format );
}

void ScriptConsoleEdit::appendExceptionText(const QString & msg, int line)
{

	QTextCharFormat format = currentCharFormat();
	QTextCharFormat exception;
	exception.setForeground( QColor("tomato") );
	exception.setFontWeight( QFont::DemiBold );
	setCurrentCharFormat(exception);
	QString message;
	if(line!=-1)
	{
		message = tr("[Exception in line %1] %2").arg(line).arg(msg);
	}
	else
	{
		message = tr("[Exception] %1").arg(msg);
	}
	appendPlainText( message );
	setCurrentCharFormat( format );
}

void ScriptConsoleEdit::appendSuccessText(const QString & msg)
{
	QTextCharFormat format = currentCharFormat();
	QTextCharFormat success;
	success.setForeground( QColor("forestgreen") );
	setCurrentCharFormat(success);
	appendPlainText( msg );
	setCurrentCharFormat( format );
}


END_NS


