#include "Root.h"

Root * Root::p_instance = NULL;

Root::Root()
{
	// !
	// NEVER CALL ANY INSTANCE OF A SINGLETON HERE! Use init instead!!!
	// !
}

Root * Root::getInstance()
{
	if(p_instance == NULL)
	{
		p_instance = new Root();
	}
	return p_instance;
}

/*Returns current GameState.*/
/*
GameState* Root::currentGameState()
{
	//  Uses GameStateManager to determine current GameState
	return mGameStateManager->get_currentGameState();
}
*/

void Root::init() //;
{
	mInputManager = InputManager::getInstance();
	mRootTransformNode = RootTransformNode::getInstance("Root");
	msc = SceneManager::getInstance();
	//get Instance to make sure a GameStateManager has been constructed
	mGameStateManager = GameStateManager::getInstance();
	mGameStateManager->init();
	mGameLoop = new GameLoop();
	
	//cout << mGameStateManager->get_currentGameState()->get_name() << endl;

	msc->initializeEngine();
	mGameLoop->startEngine(true,60,10);
}

void Root::handleInput() //;
{
	//let the InputManager do its job
	mInputManager->handle_input();
}

void Root::updateGameState()
{
	mGameStateManager->update();
}