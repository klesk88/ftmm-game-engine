#ifndef __Root_H__
#define __Root_H__
#pragma once

#include "MemoryManagement.h"
#include "SceneManager.h"
#include "GameStateManager.h"
#include "InputManager.h"
#include "GameLoop.h"
#include "RootTransformNode.h"
#include "RenderManager.h"
//#include "ResourceManager.h"
#include "GameTime.h"

class GameState;
class Event;
//#include "GameState.h"

/*Systems should only know the top level of all the sub systems*/
class Root
{
public:
	#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX Root included")
	static Root * getInstance();
	
	//singetons
	SceneManager* msc;
	InputManager* mInputManager;
	GameStateManager* mGameStateManager;
	RootTransformNode* mRootTransformNode;
	RenderManager* mRenderManager;
	GameLoop*  mGameLoop;
	//ResourceManager * mResourceManager;
	GameTime * mGameTime;
	

	/*
		- Initialize all the Singletons
		- start the Engine
	*/
	void init();

	/*Ask InputManager to do its job*/
	void handleInput();

	/*Returns current GameState.*/
	//GameState* currentGameState();

	/*Update the GameState*/
	void updateGameState(vector<Event*> events);

private:
	
	static Root* p_instance;
	~Root();
protected:
	Root();

};

#endif
