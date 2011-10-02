#include "UpdatableListener.h";

void UpdatableListener::addUpdatableObject(GameObject* game_obj){
	
		list_of_game_object.push_back(game_obj);//add the gameobject to the end of the list 
	}

void UpdatableListener::removeObject(GameObject* game_obj){
	
		list<GameObject*>::iterator i;

		for(i=list_of_game_object.begin(); i!=list_of_game_object.end();i++){
		
			if(i==game_obj){//when i found the element to remove i remove it and terminate the cycle
				list_of_game_object.erase(i);
				break;
			}
		}
	}

void UpdatableListener::notifyObjects(){
	
		list<GameObject*>::iterator ;
		EventHandler eh;
		list<Event*>::iterator ev;

		for(i=list_of_game_object.begin(); i!=list_of_game_object.end();i++){//for every object
			for(ev=eh.list_of_events.begin(); ev!=eh.list_of_events.end();ev++){//pass every event
				i->update(ev);
			}
		}
	}

	//~FrameListener() the destructor have to be created
