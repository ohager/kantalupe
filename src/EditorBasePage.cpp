#include "EditorBasePage.h"
#include "PlainTextEdit.h"
#include "LineEdit.h"
#include "Overlay.h"
#include "global.h"

#include <QtGui>

START_NS

EditorBasePage::EditorBasePage(QWidget * parent)
	: QWidget(parent),
	  mBuddyItem(0x0),
	  mDelayedCommitTriggered(false),
	  mCommitDelay(250)
{
}

EditorBasePage::~EditorBasePage()
{
	  mBuddyItem=0x0;
}

bool EditorBasePage::isAcceptingMime(const QMimeData *m) const
{
	return false;
}

void EditorBasePage::commit() const
{
	commit(buddyItem());
}

void EditorBasePage::delayedCommit() const
{
	if(!mDelayedCommitTriggered)
	{
		mDelayedCommitTriggered = true;
		QTimer::singleShot(mCommitDelay, (QObject*)this, SLOT(__delayedCommitHelper()));
	}
}

void EditorBasePage::__delayedCommitHelper() const
{
	mDelayedCommitTriggered = false;
	commit(buddyItem());
}

void EditorBasePage::commit(TreeItem * item) const
{
	Q_ASSERT_X(mBuddyItem,"ItemEditorBasePage::commit()", "Commit must follow to update()...no buddy bound");
}

void EditorBasePage::update(TreeItem * item)
{
	mBuddyItem = item;
}




END_NS

