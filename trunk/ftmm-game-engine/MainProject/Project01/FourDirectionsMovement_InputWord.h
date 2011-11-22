#ifndef FourDirectionsMovement_InputWord_H
#define FourDirectionsMovement_InputWord_H

#include "InputWord.h"
#include "FourDirectionsMovement_InputEvent.h"

class FourDirectionsMovement_InputWord: public InputWord
{

private:	
	bool north;
	bool east;
	bool south;
	bool west;

public:
	FourDirectionsMovement_InputWord(int count_gameStates) : InputWord(count_gameStates)
	{
		north = false;
		east = false;
		south = false;
		west = false;
	}

	InputEvent* update(SDL_Event _event)
	{
		//cout << "update entered" << endl;

		FourDirectionsMovement_InputEvent* fourDirectionalMovementEvent = new FourDirectionsMovement_InputEvent();
		event_current = _event;

		 switch(_event.type)
		{
			case SDL_KEYDOWN:

				//NORTH
				if(_event.key.keysym.sym == SDLK_w)
				{
					north = true;
					fourDirectionalMovementEvent->set_north(true);
					cout << "www" << endl;
				} 
				else 
				{
					north = false;
					fourDirectionalMovementEvent->set_north(false);
				}
				
				//EAST
				if(_event.key.keysym.sym == SDLK_d)
				{
					east = true;
					fourDirectionalMovementEvent->set_east(true);
					cout << "ddd" << endl;
				}
				else 
				{
					east = false;
					fourDirectionalMovementEvent->set_east(false);
				}
				
				//SOUTH
				if(_event.key.keysym.sym == SDLK_s)
				{
					south = true;
					fourDirectionalMovementEvent->set_south(true);
					cout << "sss" << endl;
				}
				else 
				{
					south = false;
					fourDirectionalMovementEvent->set_south(false);
				}
				
				//WEST
				if(_event.key.keysym.sym == SDLK_a)
				{
					west = true;
					fourDirectionalMovementEvent->set_west(true);
					cout << "aaa" << endl;
				}
				else 
				{
					west  = false;
					fourDirectionalMovementEvent->set_west (false);
				}

				fourDirectionalMovementEvent->set_eventHasOccured(true);

				break;
		 
			default:
				// TODO warn that an event that is not useful has been sent, and this should not happen!!!
				cout << "WARNING: An InputWord has received an input event that is not handled in the switch/case" << endl;

				break;
		}

		 //cout << "type in MMIW:" << typeid(cameraMovementEvent).name() << endl;
		 return fourDirectionalMovementEvent;
		//throw an MouseMovement event that has velocity, position, etc.
	}
};

#endif



