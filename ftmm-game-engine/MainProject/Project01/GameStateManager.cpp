#include "GameStateManager.h"
#include "GamePlay_01.h"

GameStateManager * GameStateManager::p_instance = NULL;

GameStateManager::GameStateManager()
{

}

GameStateManager * GameStateManager::getInstance()
{
	if(p_instance == NULL)
	{
		p_instance = new GameStateManager();
	}
	return p_instance;
}

GameState* GameStateManager::get_currentGameState()
{
	return gamePlay_01;//gameStates.back();
}

bool GameStateManager::init()
{
	gamePlay_01 = GamePlay_01::getInstance();
	gamePlay_01->init();
	gameStates.push_back(gamePlay_01);
	return true;
}

bool GameStateManager::update(vector<Event*> events)
{
	cout << "in gamestatemanager update" << endl;
	//gameStates.back()...
	gamePlay_01->update(events);
	return 0;
}