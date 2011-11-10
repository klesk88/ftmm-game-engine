#ifndef __Root_H__
#define __Root_H__
#pragma once


#include "SceneManager.h"

#include "GameStateManager.h"
#include "InputManager.h"
#include "GameLoop.h"


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
	GameLoop*  mGameLoop;

	void init() //;
{
	mInputManager = InputManager::getInstance();
	msc = SceneManager::getInstance();
	//get Instance to make sure a GameStateManager has been constructed
	mGameStateManager = GameStateManager::getInstance();
	mGameStateManager->init();
	mGameLoop = new GameLoop();
	
	
	//cout << mGameStateManager->get_currentGameState()->get_name() << endl;

	msc->initializeEngine();
	mGameLoop->startEngine(true,60,10);
}
	
	void handleInput() //;
	{
		//let the InputManager do its job
		mInputManager->handle_input();
	}

	/*Returns current GameState.*/
	//GameState* currentGameState();

	void updateGameState() //;
	{
		mGameStateManager->update();
	}


private:
	static Root* p_instance;
	~Root();
protected:
	Root();

};

#endif
