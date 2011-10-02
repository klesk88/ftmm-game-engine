#include "Event.h"

Event::Event(){

	cycles=1;
	milliseconds=1;
}

void Event::updateCycles(){

	//cycles -= SDL_GetTicksCount() - tick;
}

void Event::updateTime(){

	milliseconds -= SDL_GetTicks() - start;
}

void Event::setInitialClock(double clock){

	cycles=clock;
	//tick=SDL_GetTickCount();
}

void Event::setInitialTime(int time){
	milliseconds = time; 
	start=SDL_GetTicks();
}