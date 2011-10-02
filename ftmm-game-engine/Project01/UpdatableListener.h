#ifndef __UpdatableListener_h__
#define __UpdatableListener_h__

#include "EventHandler.h"
//#include "GameObject.h"; 
using namespace std;

//this class must cbe changed. We don't use template but GameObjects. It's like that only for debug puropose and only until we don't have the right objects

template <class T>
class UpdatableListener{
private:
	list<T*> list_of_game_object;//list containing all the game objects connected with this frame listener

public:
	void addUpdatableObject(T* game_obj);
	void removeObject(T* game_obj);
	void notifyObjects();

};

#endif