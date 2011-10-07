#include "SDL.h"
#include "SDL_opengl.h"
#include <windows.h>

#ifndef Event_H
#define Event_H

// CARE: This needs to have a virtual method for dynamic cast to work! 

class Event{//must be an interface for all the events

public:	
		double cycles;//@ param number of cycles
		int start;
		DWORD milliseconds;//@param  number of milliseconds
		float tick;
		
		Event();
		/*
			time of life of the the event, before it die
		*/
		virtual void timeOfLife(){};
		//virtual void timeOfLife()=0;
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
		void setInitialTime(int time);

		/*
		@warning
			set the clock variable
		*/
		void setInitialClock(double clock);

};

#endif