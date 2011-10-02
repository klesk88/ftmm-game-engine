#pragma once//include only one time on the compilation this file
#ifndef __EventHandler_h__
#define __EventHandler_h__

#include "Event.h"
using std::list;

class EventHandler{
public:
	list<Event*>list_of_events;//list containing all the game objects connected with this frame listener

	void addEvents(Event& ev);
	void removeEvents();
};
#endif