#ifndef ITEMEDITORMODELPAGE_H
#define ITEMEDITORMODELPAGE_H

#include "EditorBasePage.h"

class QComboBox;

namespace k{

class LineEdit;


class ItemEditorModelPage : public EditorBasePage
{
    Q_OBJECT
public:
    explicit ItemEditorModelPage(QWidget *parent = 0);
	virtual bool isAcceptingMime(const QMimeData *m) const;

	/**
	  Binds passed item as buddy to this page and updates this page with item'S data.
	  Subclasses need to override this method. Always make a super call to this class first.
	  @param item The model item
	  */
	virtual void update(TreeItem * item);

protected:

	virtual void commit(TreeItem * item) const;


protected slots:
	void onChangeUidMode();
private:
	void setupUi();
	k::LineEdit * mNameTextEdit;
	QComboBox * mUidModeComboBox;
};

} // eons

#endif // ITEMEDITORMODELPAGE_H
