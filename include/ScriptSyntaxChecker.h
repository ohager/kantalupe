#ifndef SCRIPTSYNTAXCHECKER_H
#define SCRIPTSYNTAXCHECKER_H

#include <QObject>
#include <QPlainTextEdit>

namespace k{

class ScriptTextEdit;

class ScriptSyntaxChecker : public QObject
{
    Q_OBJECT
public:
	explicit ScriptSyntaxChecker(ScriptTextEdit * editor, QObject *parent = 0);

public slots:
	void checkSyntax();


private slots:
	void __delayedSyntaxCheck();
	void __destroyed();
private:
	ScriptTextEdit * _textEdit;
	mutable bool mAlreadyAdded;
};

} // eons

#endif // SCRIPTSYNTAXCHECKER_H
