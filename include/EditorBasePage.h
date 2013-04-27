#ifndef EditorBasePage_H
#define EditorBasePage_H

#include <QWidget>


class QMimeData;

namespace k{

	class TreeItem;
	/**
	  The base Editor page.
	  Subclassing is necessary.
	  @par Update and Commit
	  Before committing the data, the page needs an associated model item.
	  This relation is established on update(ModelTreeDataItem*) and exists
	  until the next update-call. The associated item is available via buddyItem().
	  So, calling commit() @e before any update-call leads to undefined behaviour.
	  All subclasses need to override commit/update. Each implementation needs a
	  super call to this class first!
	  @author O. Haeger
	  */
	class EditorBasePage : public QWidget
	{
		Q_OBJECT
	public slots:
		/**
		  Commits any data from this editor page to buddyItem();
		  Need to be called @e after update()
		  */
		void commit() const;

		/**
		  Commits data after a specified delay ( setCommitDelay() ). All calls to this slot within that period,
		  are bundled to one call only. This function is useful, if many commits may occur
		  within a (very) short period.
		  @see setCommitDelay()
		  */
		void delayedCommit() const;

	public:
		EditorBasePage(QWidget * parent=0x0);
		virtual ~EditorBasePage();

		/**
		  @return @e true if a mime type is accepted, otherwise false.
		  Base implementation returns always false.
		  */
		virtual bool isAcceptingMime(const QMimeData *m) const;


		/**
		  Binds passed item as buddy to this page and updates this page with item'S data.
		  Subclasses need to override this method. Always make a super call to this class first.
		  @param item The model item
		  */
		virtual void update(TreeItem * item);

	protected:

		virtual void commit(TreeItem * item) const;

		inline int getCommitDelay() const { return mCommitDelay;  }
		/**
		  Sets the commit delay for delayedCommit().
		  @param msecs The delay used by delayedCommit() in milliseconds.
		  @see getCommitDelay()
		  */
		inline void setCommitDelay(int msecs) { mCommitDelay=msecs;  }
		/**
		  Binds passed item as buddy to this page.
		  Subclasses need to override this method. Always make a super call to this class first.
		  @param item The model item, i.e. the buddyItem();
		  */


		/**
		  The associated item. The relation is established on update()-call.
		  */
		inline TreeItem * buddyItem() const { return mBuddyItem; }

	private slots:
		void __delayedCommitHelper() const;

	private:

		TreeItem * mBuddyItem;
		mutable bool mDelayedCommitTriggered;
		int mCommitDelay;
	};

} // eons
#endif // ItemEditorBasePage_H
