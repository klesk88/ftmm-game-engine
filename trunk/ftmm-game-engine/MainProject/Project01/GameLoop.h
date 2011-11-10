#ifndef GameLoop_H
#define GameLoop_H

#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include <list>


class FrameListener;

class GameLoop
{
private:

		bool gameLoop(const int base_fps,const int low_fps);

		//For FPS calculation
		Uint32 startclock;
		Uint32 deltaclock;
		Uint32 currentFPS;

public:

		/*	@Param base_fps: how many fps you want
			@Param low_fps: minimum fps for having game logic at base fps speed
		*/
		void callGameLoop(bool,const int base_fps,const int low_fps);
		void createFrameListener(FrameListener*);
		/*
			i set the game_is:run variable so i know if the game loop have to start or not.
			after i call the method for call the game loop with the right parameters		
		*/
		void startEngine(bool,const int base_fps,const int low_fps);
		std::list <FrameListener*> framelistener_list;


};

#endif