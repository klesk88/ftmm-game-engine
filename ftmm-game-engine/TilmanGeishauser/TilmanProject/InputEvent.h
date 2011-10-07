#include "Event.h"

#ifndef InputEvent_H
#define InputEvent_H

class InputEvent: public Event 
{

protected:
	bool eventHasOccured;

public:
	InputEvent() : Event()
	{
		eventHasOccured = false;
	}
	~InputEvent(){}

	bool get_eventHasOccured()
		{ return eventHasOccured;};
	void set_eventHasOccured(bool current_eventHasOccured)
		{ eventHasOccured = current_eventHasOccured;}

};

#endif