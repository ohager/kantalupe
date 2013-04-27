#ifndef ITEMEDITORMATRIXPAGE_H
#define ITEMEDITORMATRIXPAGE_H
#include "EditorBasePage.h"

namespace k{

class ImageListWidget;
class PlainTextEdit;
class LineEdit;

class ItemEditorMatrixPage : public EditorBasePage
{
    Q_OBJECT
public:
	ItemEditorMatrixPage(QWidget * parent = 0);

public:
	bool isAcceptingMime(const QMimeData *m) const;
	void update(TreeItem *item);
protected:
	void commit(TreeItem *item) const;

private:
	void setupUi();

	k::ImageListWidget * mImageList;
	k::PlainTextEdit * mQuestionTextEdit,
					* mHintTextEdit;
	k::LineEdit * mNameLineEdit;
};

} // eons

#endif // ITEMEDITORMATRIXPAGE_H
