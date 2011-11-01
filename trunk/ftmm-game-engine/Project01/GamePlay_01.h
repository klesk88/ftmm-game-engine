#ifndef __GamePlay_01_H__
#define __GamePlay_01_H__

#include "IGameState.h"

#pragma once

// You could also call this our first level
class GamePlay_01 : IGameState
{
	private:
		static GamePlay_01 * p_instance;
		~GamePlay_01();
	protected:
		GamePlay_01();
	public:
		static GamePlay_01 * getInstance ();
		void init();
};
#endif
