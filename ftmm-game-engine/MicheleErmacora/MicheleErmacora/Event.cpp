#include "Event.h"

Event::Event(){

	cycles=1;
	milliseconds=1;
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

void Event::setInitialTime(int time){
	milliseconds = time; 
	start=SDL_GetTicks();
}