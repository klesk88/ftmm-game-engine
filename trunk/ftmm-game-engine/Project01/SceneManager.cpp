#include "SceneManager.h"

SceneManager::SceneManager(){

	root_ptr = RootTransformNode::getInstance("Root",0.0,0.0,0.0);
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
