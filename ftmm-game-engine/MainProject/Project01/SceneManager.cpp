#include "SceneManager.h"
#include "Root.h"


SceneManager::SceneManager()
{
	//Root *mRoot = Systems::getInstance();
	//std::cout << "listen: " << mRoot->get_current_GameState()->name() << std::endl;
	//mRoot->gamePlay_01->loadStuff();

	//FORT TESTING ONLY
	translate_ratio = 0.0;
	pos = Vector2(0.0,0.0);

	//game_is_run=false;//by default the game is run state is set to false so the game loop doesn't start until the user start it
	//root_ptr = RootTransformNode::getInstance("Root");
	root_ptr = Root::getInstance()->mRootTransformNode;
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

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	std::list<Camera*>::iterator cam_it;

	for ( cam_it = camera_list.begin(); cam_it != camera_list.end(); ++cam_it){
	
		(**cam_it).updateCamera();
		this->getRootTransformNode()->updateNode();

	}

	SDL_GL_SwapBuffers();
}




//deleteEngine

		/* clean ourselves up and exit */
		//Quit( 0 );
