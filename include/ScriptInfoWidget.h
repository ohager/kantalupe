#ifndef SCRIPTINFOWIDGET_H
#define SCRIPTINFOWIDGET_H

#include <QWidget>
#include <QDate>

class QComboBox;

namespace k{

class LineEdit;
class PlainTextEdit;
class Script;

/**
  Widget for entering script information.
  @author O.Hager
  */
class ScriptInfoWidget : public QWidget
{
    Q_OBJECT
public:

	ScriptInfoWidget(QWidget *parent = 0);

	/**
	  Sets script data for this widget
	  @param script The script data object
	  @see toScript()
	  */
	void fromScript(const Script & script);
	/**
	  @return A script object with all entered information. The script object
	  @e does not have the program data, but only its information. Furthermore,
	  the script may not be complete.
	  */
	Script toScript() const;

	QString getName() const;
	void  setName(const QString &);

	QString getDescription() const;
	void  setDescription(const QString &);

	QString getAuthor() const;
	void  setAuthor(const QString &);

	QString getVersion() const;
	void  setVersion(const QString &);

	QDate getLastEdited() const;
	void  setLastEdited(const QDate &);

	int getApiLevel() const;
	void  setApiLevel(int);


protected:
	void showEvent(QShowEvent *);
private:
	void setupUi();
	PlainTextEdit * mDescription;
	LineEdit * mAuthor,
			* mVersion,
			* mLastEdited,
			* mName,
			* mApiLevel;
};


} // eons

#endif // SCRIPTINFOWIDGET_H
