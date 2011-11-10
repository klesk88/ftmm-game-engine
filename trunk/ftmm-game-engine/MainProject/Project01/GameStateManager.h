#ifndef __GameStateManager_h__
#define __GameStateManager_h__
#pragma once

#include <vector>
using namespace std;

class GamePlay_01;
class GameState;

class GameStateManager
{
private:
	static GameStateManager * p_instance;
	~GameStateManager();

	vector<GameState*> gameStates;
	GamePlay_01 * gamePlay_01;

protected:
	GameStateManager();

public:
	#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX GameStateManager included")
	static GameStateManager * getInstance ();

	GameState* get_currentGameState();

	bool init();
	bool update();


};


#endif