#ifndef ABSTRACTEDITOR_H
#define ABSTRACTEDITOR_H


#include <QWidget>


class QListWidget;
class QListWidgetItem;
class QStackedWidget;

namespace k{


class AbstractEditor : public QWidget
{
	Q_OBJECT

public:
	AbstractEditor (QWidget * parent=0x0);
	~AbstractEditor();


	inline QListWidget * pageSelector() const { return mPageSelector; }
	/**
	  Adds a page.
	  @param page The page. The editor will take control over page
	  @param icon The icon, that represents the page in pageSelector()
	  @param text The text,  that represents the page in pageSelector()
	  @param tooltip [optional] The tool tip text, that appears when hovering in pageSelector()
	  @return The index for added page.
	  */
	int addPage(QWidget * page, const QIcon & icon, const QString & text, const QString & tooltip=QString());
protected:
	/**
	  Event when page @e is @e about to change
	  @param page The page that will changed to.
	  @note This is immediately called before page changes.
	  */
	virtual void aboutToChangePage(QWidget * page);


private slots:
	void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private:
	QListWidget * mPageSelector;
	QStackedWidget * mPagesWidget;
};

} // eons

#endif // AbstractEditor_H

