#ifndef EngineControls_InputWord_H
#define EngineControls_InputWord_H

#include "InputWord.h"
#include "EngineControls_InputEvent.h"

class EngineControls_InputWord: public InputWord
{

private:	
	int gotoGameState;

	bool keypress_combination01_key01;
	bool keypress_combination01_key02;
	bool keypress_combination01_key03;
	bool keypress_combination01_key04;
	bool keypress_combination01_key05;


public:
	EngineControls_InputWord(int count_gameStates) : InputWord(count_gameStates)
	{
		gotoGameState = -1;
		keypress_combination01_key01 = false;
		keypress_combination01_key02 = false;
		keypress_combination01_key03 = false;
		keypress_combination01_key04 = false;
		keypress_combination01_key05 = false;
	}

	InputEvent* update(SDL_Event _event)
	{
		EngineControls_InputEvent* engineControlsMovementEvent = new EngineControls_InputEvent();
		event_current = _event;

		switch(_event.type)
		{
			case SDL_KEYDOWN:

				switch (_event.key.keysym.sym)
				{
					case SDLK_k:
						keypress_combination01_key01 = true;
						break;
					case SDLK_1:
						keypress_combination01_key02 = true;
						break;
					case SDLK_2:
						keypress_combination01_key03 = true;
						break;
					case SDLK_3:
						keypress_combination01_key04 = true;
						break;
					case SDLK_4:
						keypress_combination01_key05 = true;
						break;
					default:
						break;
				}
				break;

            case SDL_KEYUP:
                switch(_event.key.keysym.sym)
				{
					case SDLK_k:
						keypress_combination01_key01 = false;
						break;
					case SDLK_1:
						keypress_combination01_key02 = false;
						break;
					case SDLK_2:
						keypress_combination01_key03 = false;
						break;
					case SDLK_3:
						keypress_combination01_key04 = false;
						break;
					case SDLK_4:
						keypress_combination01_key05 = false;
						break;
					default:
						break;
                }
				break;
		 
			default:
				// TODO warn that an event that is not useful has been sent, and this should not happen!!!
				cout << "WARNING: An InputWord has received an input event that is not handled in the switch/case" << endl;

				break;
		}

		if (keypress_combination01_key01)
		{
			if(keypress_combination01_key02) gotoGameState = 1;
			if(keypress_combination01_key03) gotoGameState = 2;
			if(keypress_combination01_key02) gotoGameState = 3;
		}


		cout << "GAME STATE: " << gotoGameState << endl;
		engineControlsMovementEvent->set_eventHasOccured(true);

		 //cout << "type in MMIW:" << typeid(cameraMovementEvent).name() << endl;
		 return engineControlsMovementEvent;
		//throw an MouseMovement event that has velocity, position, etc.
	}
};

#endif



