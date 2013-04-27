#ifndef UserModeEvent_H
#define UserModeEvent_H

#include <QEvent>
#include "global.h"
// extend the type enum

namespace k{

	/**
	  The event for mode events
	  @author O. Haeger
	  */
	class UserModeEvent : public QEvent
	{
	public:

		explicit UserModeEvent(global::UserModeType cur,
							   global::UserModeType prev);
		~UserModeEvent();
		inline global::UserModeType previousUserMode() const { return mPrevMode; }
		inline global::UserModeType userMode() const { return mMode; }

	private:
		global::UserModeType mMode, mPrevMode;
	};

} // eons

#endif // UserModeEvent_H
