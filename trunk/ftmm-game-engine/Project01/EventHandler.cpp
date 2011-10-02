#include "EventHandler.h";



void EventHandler::addEvents(Event* ev){
	
		list_of_events.push_back(ev);//add an event to the end of the list 
	}


void EventHandler::removeEvents(){
	
		list_of_events.remove(0);//remove the event in first position because is the event compelete
	}
