#ifndef __GameStateManager_h__
#define __GameStateManager_h__
#pragma once

#include <vector>
class Event;

using namespace std;

class GamePlay_01;
class GamePlay_02;
class GameState;


class GameStateManager
{
public:
	//#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX GameStateManager included")
	enum EGameState
	{
		GAMEPLAY_01 = 0,
		GAMEPLAY_02
	};

	static GameStateManager * getInstance ();

	GameState* get_currentGameState();

	bool init();
	bool update(vector<Event*> events);
	bool transitToGameState(EGameState state);

protected:
	GameStateManager();

private:
	static GameStateManager * p_instance;
	~GameStateManager();

	vector<GameState*> gameStates;
	GamePlay_01 * gamePlay_01;
	GamePlay_02 * gamePlay_02;
};


#endif