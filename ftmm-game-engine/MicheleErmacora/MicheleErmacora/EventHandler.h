#pragma once//include only one time on the compilation this file
#ifndef __EventHandler_h__
#define __EventHandler_h__
#include <vector>
#include "Event.h"


class EventHandler{

public:
	std::vector <Event*> vector_of_events;//list containing all the game objects connected with this frame listener

	void addEvents(Event* ev);
	void removeEvents();
	(std::vector<Event*>)* returnVectorOfEvents();
};
#endif