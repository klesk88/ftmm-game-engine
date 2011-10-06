#include "Event.h"

Event::Event(){

	cycles=1;
	milliseconds=1;
	priority=0;
}

void Event::updateCycles(){

	cycles -= clock() - tick;
}

void Event::updateTime(){

	milliseconds -= SDL_GetTicks() - start;
}

void Event::setInitialClock(clock_t clo){

	cycles=clo;
	tick = clock();
}

void Event::setInitialTime(DWORD time){
	milliseconds = time; 
	start=SDL_GetTicks();
}

void Event::setPriority(int priority){

	this->priority=priority;
}

int Event::getPriority(){

	return priority;
}