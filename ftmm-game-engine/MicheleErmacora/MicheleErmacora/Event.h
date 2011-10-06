#ifndef __Event_h__
#define __Event_h__

#include "SDL.h"
#include "SDL_opengl.h"
#include <windows.h>
#include <ctime>


class Event{//must be an interface for all the events

public:	
		clock_t cycles;//@ param number of clock ticks
		DWORD start;
		DWORD milliseconds;//@param  number of milliseconds
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
		virtual void setInitialTime(DWORD time);

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

private:

	int priority;
	
};

#endif