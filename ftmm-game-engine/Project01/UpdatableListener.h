#ifndef __UpdatableListener_h__
#define __UpdatableListener_h__

#include "EventHandler.h"
//#include "GameObject.h"; 
using namespace std;

;
class UpdatableListener{
private:
	list<GameObject*> list_of_game_object;//list containing all the game objects connected with this frame listener

public:

	void addUpdatableObject(GameObject* game_obj);
	void removeObject(GameObject* game_obj);
	void notifyObjects();

};

#endif