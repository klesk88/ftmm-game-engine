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

