#include "SceneManager.h"


SceneManager::SceneManager(){

	//game_is_run=false;//by default the game is run state is set to false so the game loop doesn't start until the user start it
	root_ptr = RootTransformNode::getInstance("Root");
}



SceneManager * SceneManager::p_instance = NULL;

SceneManager * SceneManager::getInstance(){

	if(p_instance == NULL){
	
		p_instance = new SceneManager();

	}

	return p_instance;

}

TransformNode * SceneManager::getRootTransformNode(){

	return root_ptr;
}

Camera * SceneManager::createCamera(const std::string  & stringName){


	Camera * cam = new Camera (stringName);
	camera_list.push_back(cam);

	return cam;

}

void SceneManager::renderScene(){

	std::list<Camera*>::iterator cam_it;

	for ( cam_it = camera_list.begin(); cam_it != camera_list.end(); ++cam_it){
	
		(**cam_it).updateCamera();
		this->getRootTransformNode()->updateNode();

	}

}

void SceneManager::callGameLoop(bool game_is_run,const int base_fps,const int low_fps){
	while(game_is_run)
	{
		game_is_run = gameLoop(base_fps,low_fps);

	}
}

void SceneManager::createFrameListener(FrameListener* frame){

	framelistener_list.push_back(frame);
}

void SceneManager::startEngine(bool game_is_run,const int base_fps,const int low_fps){

	callGameLoop(game_is_run,base_fps,low_fps);
}


bool SceneManager::gameLoop(const int base_fps,const int low_fps){
		const int TICKS_PER_SECOND = base_fps;
		const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
		const int MAX_FRAMESKIP = low_fps;
	    DWORD next_game_tick = SDL_GetTicks();
		int loops;
		bool game_is_run=true;
		std::list<FrameListener*>::iterator i;
		
		

		   loops = 0;
		   while( unsigned int(SDL_GetTicks() - next_game_tick) > SKIP_TICKS && loops < MAX_FRAMESKIP) {
				
			   for(i=framelistener_list.begin(); i!=framelistener_list.end();i++){
				   if(  (*i)->frameStarted())
					   game_is_run = (*i)->getEvents();		
			   }
			   next_game_tick += SKIP_TICKS;
			   loops++;
			}
		   //drawGLScene();
		for(i=framelistener_list.begin(); i!=framelistener_list.end();i++){
			(*i)->frameEnded();		
		}
		return game_is_run;
}
