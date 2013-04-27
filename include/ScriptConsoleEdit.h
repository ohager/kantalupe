#ifndef SCRIPTCONSOLEEDIT_H
#define SCRIPTCONSOLEEDIT_H

#include "PlainTextEdit.h"

namespace k{

class ScriptConsoleEdit : public PlainTextEdit
{
	Q_OBJECT

public:
	ScriptConsoleEdit(QWidget * parent = 0x0);
public slots:

	void appendDebugText(const QString & msg);
	void appendWarningText(const QString & msg, int line);
	void appendExceptionText(const QString & msg, int line);
	void appendSuccessText(const QString & msg);
private:
	void setupUi();
};


} // eons
#endif // SCRIPTCONSOLEEDIT_H
