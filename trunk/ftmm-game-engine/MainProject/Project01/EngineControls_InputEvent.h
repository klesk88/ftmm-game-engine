#ifndef EngineControls_InputEvent_H
#define EngineControls_InputEvent_H

#include "InputEvent.h"

class EngineControls_InputEvent: public InputEvent 
{
//private:


public:
	EngineControls_InputEvent() : InputEvent()
	{
		eventHasOccured = false;
	}


};

#endif