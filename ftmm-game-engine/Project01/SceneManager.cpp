#include "SceneManager.h"

SceneManager::SceneManager(){

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
