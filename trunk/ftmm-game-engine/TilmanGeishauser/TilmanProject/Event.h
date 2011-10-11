#ifndef __Event_h__
#define __Event_h__

#include "SDL.h"
#include "SDL_opengl.h"
#include <windows.h>
#include <ctime>
#include <vector>

class Event{//must be an interface for all the events

public:	
		clock_t cycles;//@ param number of clock ticks
		unsigned int start;
		unsigned int milliseconds;//@param  number of milliseconds
		clock_t tick;
		

		Event();
		/*
		@warning
			update the time of the object based
			on the ticks of the cpu clock
		*/
		virtual void updateCycles();
		/*
		@warning
			update the time of the object based
			on milliseconds		
		*/
		virtual void updateTime();
		/*
		@warning
			set the time variable in milliseconds
		*/
		virtual void setInitialTime(unsigned int time);

		/*
		@warning
			set the clock variable
		*/
		virtual void setInitialClock(clock_t clo);

		/*
			set the priority of the event
		*/
		void setPriority(int);
		int getPriority();
		void setStartEndIndex(std::vector<Event*>::iterator start,std::vector<Event*>::iterator end);
		std::vector<Event*>::iterator getStartIndex();
		std::vector<Event*>::iterator getEndIndex();
private:

	int priority;

	//start and end of the type of event inside the vector list
	std::vector<Event*>::iterator started,end;
};

#endif