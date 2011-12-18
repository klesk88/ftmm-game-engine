#ifndef CameraMovementInputWord_H
#define CameraMovementInputWord_H

#include "InputWord.h"
#include "Vector2.h"
#include "CameraMovementInputEvent.h"

class CameraMovementInputWord: public InputWord
{

public:
	#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX CameraMovementInputWord included")
	CameraMovementInputWord(int count_gameStates) : InputWord(count_gameStates){}

	InputEvent* update(SDL_Event _event)
	{

		Vector2 position_cur;
		int x;
		int y;

		CameraMovementInputEvent* cameraMovementEvent = new CameraMovementInputEvent();

		event_current = _event;

		 switch(_event.type)
		{
			case SDL_MOUSEMOTION:

				x =_event.motion.x;
				y =_event.motion.y;
				position_cur = Vector2(x,y);

				cameraMovementEvent->set_current_position(position_cur);
				cameraMovementEvent->set_eventHasOccured(true);

				break;
		 
			default:
				// TODO warn that an event that is not useful has been sent, and this should not happen!!!
				cout << "WARNING: An InputWord has received an input event that is not handled in the switch/case" << endl;
				break;
		}

		 return cameraMovementEvent;
		//throw an MouseMovement event that has velocity, position, etc.
	}
};

#endif


