#ifndef __Event_h__
#define __Event_h__

#include "SDL.h"
#include "SDL_opengl.h"
#include <windows.h>
#include <ctime>
#include <string>

class Event{//must be an interface for all the events

public:	
		clock_t cycles;//@ param number of clock ticks
		DWORD start;
		DWORD milliseconds;//@param  number of milliseconds
		clock_t tick;
		int priority;
		std::string name;

		Event();
		/*
		@warning
			time of life of the the event, before it die
		*/
		virtual void timeOfLife()=0;
		/*
		@warning
			update the time of the object based
			on the ticks of the cpu clock
		*/
		void updateCycles();
		/*
		@warning
			update the time of the object based
			on milliseconds		
		*/
		void updateTime();
		/*
		@warning
			set the time variable in milliseconds
		*/
		void setInitialTime(DWORD time);

		/*
		@warning
			set the clock variable
		*/
		void setInitialClock(clock_t clo);

		/*
			set the priority of the event
		*/
		void setPriority(int);

	
};

#endif