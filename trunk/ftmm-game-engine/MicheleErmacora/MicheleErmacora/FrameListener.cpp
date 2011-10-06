#include "FrameListener.h"

FrameListener::FrameListener(EventHandler* e){

	ev=e;
}

void FrameListener::addUpdatableObject(GameObject* game_obj){

	vector_of_game_object.push_back(game_obj);//add the gameobject to the end of the list 
}

void FrameListener::removeObject(GameObject* game_obj){

	vector_of_game_object.erase(vector_of_game_object.begin());//add the gameobject to the end of the list 
}

void FrameListener::notifyObjects(){
	vector<GameObject*>::iterator i;
	EventHandler eh;

		for(i=vector_of_game_object.begin(); i!=vector_of_game_object.end();i++){//for every object
			(*i)->update(ev->returnVectorOfEvents());
		}
}