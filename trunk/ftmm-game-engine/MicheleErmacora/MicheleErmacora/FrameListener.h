#include "EventHandler.h"
#include "GameObject.h"
#ifndef __FrameEvent_h__
#define __FrameEvent_h__

/*struct FrameEvent
     {
         float timeSinceLastEvent;
         float timeSinceLastFrame;
     };
*/// Ogre stuff in case we want to implement
using std::vector;


class FrameListener{
private:
	EventHandler* ev;
	vector<GameObject*> vector_of_game_object;//list containing all the game objects connected with this frame listener
public:
	FrameListener(EventHandler*);
	virtual bool frameStarted()
	{return true;}
	virtual bool frameEnded()
	{return true;}
	void addUpdatableObject(GameObject* game_obj);
	void removeObject(GameObject* game_obj);
	void notifyObjects();
};

#endif