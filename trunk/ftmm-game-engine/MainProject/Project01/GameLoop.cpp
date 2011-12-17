#include "GameLoop.h"
#include "Root.h"

void GameLoop::callGameLoop(bool game_is_run,const int base_fps,const int low_fps){
	
	// for FPS counting
	startclock = SDL_GetTicks();
	
	TICKS_PER_SECOND = base_fps;
	SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	MAX_FRAMESKIP = low_fps;
	next_game_tick = SDL_GetTicks();

	while(game_is_run)
	{
		game_is_run = gameLoop(base_fps,low_fps);

	}
}

/*
void GameLoop::createFrameListener(FrameListener* frame){

	framelistener_list.push_back(frame);
}
*/
void GameLoop::startEngine(bool game_is_run,const int base_fps,const int low_fps){

	callGameLoop(game_is_run,base_fps,low_fps);
}


bool GameLoop::gameLoop(const int base_fps,const int low_fps)
{
	int loops;
	bool game_is_run=true;
	std::list<FrameListener*>::iterator i;
		
	loops = 0;
	while( unsigned int(SDL_GetTicks() - next_game_tick) > SKIP_TICKS && loops < MAX_FRAMESKIP) 
	{
		//count total number of game updates one up
		Root::getInstance()->mGameTime->increase_totalUpdatesSinceStart();

		//Can be used for debugging
		//int totalupdatessincestart = Root::getInstance()->mGameTime->get_totalUpdatesSinceStart();
		//cout << "Game Logic update: " << totalupdatessincestart << endl;

		Root::getInstance()->handleInput();
		//event_list.clear();
	
		// get input events
		vector<Event*> input_events  = Root::getInstance()->mInputManager->get_input_events();

		// if input events have occured
		if(Root::getInstance()->mInputManager->get_input_events().empty() == false)
		{
			for (vector<Event*>::iterator it = input_events.begin(); it != input_events .end(); ++it) 
			{
				//check whether its a CMIE
				if(EngineControls_InputEvent * eC_IE = dynamic_cast<EngineControls_InputEvent *>(*it)) 
				{
					Root::getInstance()->mGameStateManager->transitToGameState(eC_IE->get_gameStateRequest());
				}

				//cout<< "input" <<endl;
			}
		}

		Root::getInstance()->updateGameState(input_events);
		
		//loop specific updates
		next_game_tick += SKIP_TICKS;
		loops++;
	}
	//cout << "renderrrrrrrrrrrrr" << endl;
	Root::getInstance()->msc->renderScene();

	// actual fps calculation inside loop
	deltaclock = SDL_GetTicks() - startclock;startclock = SDL_GetTicks();		
	if ( deltaclock != 0 )	currentFPS = 1000 / deltaclock;  

	//cout<<"FPS: "<<currentFPS<<endl;

	return game_is_run;
}

