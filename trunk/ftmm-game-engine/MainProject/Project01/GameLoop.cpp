#include "GameLoop.h"
#include "Root.h"


void GameLoop::callGameLoop(bool game_is_run,const int base_fps,const int low_fps){
	
	// for FPS counting
	startclock = SDL_GetTicks();
	
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


bool GameLoop::gameLoop(const int base_fps,const int low_fps){
		const int TICKS_PER_SECOND = base_fps;
		const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
		const int MAX_FRAMESKIP = low_fps;
	    DWORD next_game_tick = SDL_GetTicks();
		int loops;
		bool game_is_run=true;
		std::list<FrameListener*>::iterator i;
		
		
		Root::getInstance()->handleInput();
		
		//event_list.clear();

		// if input events have occured
		if(Root::getInstance()->mInputManager->get_input_events().empty() == false)
		{
			// get input events
			vector<Event*> temp_vector = Root::getInstance()->mInputManager->get_input_events();

			for (vector<Event*>::iterator it = temp_vector.begin(); it != temp_vector.end(); ++it) 
			{
				//check whether its a CMIE
				if(CameraMovementInputEvent * cME = dynamic_cast<CameraMovementInputEvent *>(*it)) 
				{
					Vector2 position = cME->get_current_position();
					cout << position.x << " . " << position.y << endl;
				}
			}
		}
		

		   loops = 0;
		   while( unsigned int(SDL_GetTicks() - next_game_tick) > SKIP_TICKS && loops < MAX_FRAMESKIP) 
		   {
			/*
			   for(i=framelistener_list.begin(); i!=framelistener_list.end();i++){
				   if(  (*i)->frameStarted())
					   game_is_run = (*i)->getEvents();	
			
			   }
			   */
			   next_game_tick += SKIP_TICKS;
			   loops++;
			}


		   Root::getInstance()->updateGameState();
		   Root::getInstance()->msc->renderScene();
	/*
		for(i=framelistener_list.begin(); i!=framelistener_list.end();i++){
			(*i)->frameEnded();		
		}
		*/

		// actual fps calculation inside loop
		deltaclock = SDL_GetTicks() - startclock;startclock = SDL_GetTicks();		
		if ( deltaclock != 0 )	currentFPS = 1000 / deltaclock;  
		cout<<"FPS: "<<currentFPS<<endl;

		return game_is_run;
}
