#ifndef __GameLoop_h__
#define __GameLoop_h__
#include "UpdatableListener.h";
#include "FrameListener.h";
#include "EventHandler.h"
#include "SDL.h";
#include "SDL_opengl.h";
#include <windows.h>;

class GameLoop{
public:
	GameLoop(const int base_fps,const int low_fps);
	void callGameLoop();//public functiuon that called the gameloop
	void setGameState(bool state);
private:
	bool game_is_run;
	const int base_fps; //base_fps= fps used for the game logic
	const int low_fps; //low_fps= fps used for slow-down the game logic when the rendering is too slow
	void gameLoop();//private function
};

#endif