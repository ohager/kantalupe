	#include "UserModeEvent.h"


START_NS

UserModeEvent::UserModeEvent(global::UserModeType c,
							 global::UserModeType p
							 )
	: QEvent(global::UserMode), mMode(c), mPrevMode(p)
{}


UserModeEvent::~UserModeEvent()
{ }


END_NS

