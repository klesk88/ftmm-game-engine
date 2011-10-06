

#include "EventHandler.h";



void EventHandler::addEvents(Event* ev){
	
		vector_of_events.push_back(ev);//add an event to the end of the list 
	}


void EventHandler::removeEvents(){
	
		vector_of_events.erase(vector_of_events.begin());//remove the event in first position because is the event compelete
	}

std::vector<Event*> * EventHandler::returnVectorOfEvents(){

	return &(vector_of_events);
}

