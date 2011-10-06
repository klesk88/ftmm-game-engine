#pragma once//include only one time on the compilation this file
#ifndef __EventHandler_h__
#define __EventHandler_h__
#include <vector>
#include "Event.h"
#include <typeinfo>

class EventHandler{

public:
	
	EventHandler();
	void addEvents(Event* ev);
	void removeEvents();
	(std::vector<Event*>)* returnVectorOfEvents();
	/*
		return the pointer to the initial position of the ai events (3r position)
	*/
	std::vector<Event*>::iterator returnAiStartPointer(); 
	/*
		return the pointer to the initial position of the physics events (2nd position)
	*/
	std::vector<Event*>::iterator returnPhysicsStartPointer(); 
	/*
		return the pointer to the initial position of the input events (1st postion)
	*/
	std::vector<Event*>::iterator returnInputStartPointer();

	std::vector<Event*>::iterator returnAiEndPointer(); 
	std::vector<Event*>::iterator returnPhysicsEndPointer(); 
	std::vector<Event*>::iterator returnInputEndPointer(); 

private:

	std::vector <Event*>* vector_of_events;//list containing all the game objects connected with this frame listener
	std::vector<Event*>::iterator input,physics,ai;//puntatore
	std::vector<Event*>::iterator returnIndex(std::vector<Event*>::iterator begin,std::vector<Event*>::iterator end,int);

};
#endif