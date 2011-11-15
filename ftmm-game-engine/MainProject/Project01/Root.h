#ifndef __Root_H__
#define __Root_H__
#pragma once


#include "SceneManager.h"

#include "GameStateManager.h"
#include "InputManager.h"
#include "GameLoop.h"
#include "RootTransformNode.h"

class GameState;
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
	GameLoop*  mGameLoop;

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
	void updateGameState();

private:
	static Root* p_instance;
	~Root();
protected:
	Root();

};

#endif
