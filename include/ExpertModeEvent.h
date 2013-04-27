#ifndef ExpertModeEvent_H
#define ExpertModeEvent_H

#include <QEvent>

// extend the type enum

namespace k{

	/**
	  The event for Expert mode toggles
	  @author O. Haeger
	  */
	class ExpertModeEvent : public QEvent
	{
	public:
		explicit ExpertModeEvent(bool enabled=true);
		inline bool isEnabled() const { return mEnabled; }
		inline void setEnabled(bool enabled) { mEnabled = enabled; }
	private:
		bool mEnabled;
	};

} // eons

#endif // ExpertModeEvent_H
