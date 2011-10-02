#pragma once
#include "GameLoop.h";



GameLoop::GameLoop(const int base,const int low):base_fps(base),low_fps(low)
{}

void GameLoop::setGameState(bool state){
	game_is_run=state;
}
void GameLoop::callGameLoop(){
	gameLoop();
}
	
void GameLoop::gameLoop(){
					
		const int TICKS_PER_SECOND = base_fps;
		const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
		const int MAX_FRAMESKIP = low_fps;
		UpdatableListener<int>* update = nullptr;//YOU MUST INSERT IN THE BRACKETS THE TYPE OF OBJECT YOU WANT FOR EXAMPLE INT
		FrameListener* frame = new FrameListener();
	    DWORD next_game_tick = SDL_GetTicks();//see what getticks return!!!!!!!!!!!!!!!!!!!
		int loops;

		while(game_is_run) {
			if(!frame->frameStarted()){
				break;
			}
		   loops = 0;
		   while( unsigned int(SDL_GetTicks() - next_game_tick) > SKIP_TICKS && loops < MAX_FRAMESKIP) {
				update->notifyObjects();//chiamate a classe esterna update

			    next_game_tick += SKIP_TICKS;
			   loops++;
			}

		 display_game();//drow everything
		 if(!frame->frameEnded())//if the frame return false, so we want to stop the gameloop
			 {	
			 break;
			 }
		 }
	}


