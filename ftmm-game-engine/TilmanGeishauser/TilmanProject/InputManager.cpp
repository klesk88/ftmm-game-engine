#include "InputManager.h"

InputManager::InputManager()
{
	/*
	InputWord mouse_mover(0);
	mouse_mover.set_listen_to_MouseMovement(true);
	input_words.push_back(mouse_mover);

	InputWord mouse_clicker(0);
	mouse_clicker.set_listen_to_MouseButtonPressed(true);
	input_words.push_back(mouse_clicker);

	InputWord key_clicker(0);
	key_clicker.set_listen_to_KeyStroke(true);
	input_words.push_back(key_clicker);

	InputWord key_presser(0);
	key_presser.set_listen_to_KeyState(true);
	input_words.push_back(key_presser);
	*/
	MouseMovementInputWord* cameraMotion = new MouseMovementInputWord(0);
	cameraMotion->set_listen_to_MouseMovement(true);
	input_words.push_back(cameraMotion);
	cout << "type in IM of IW:" << typeid(cameraMotion).name() << endl;
}


// makes a coarse pre-selection on which InputWords to update, goes into the case which handles the current input and then iterates through 
// the vector containing the Input word (bot operations have O(n)). This is faster than updating every vector (already O(n) for calling).
InputManager::SIGNAL InputManager::handle_input(){

    //Poll to see if we have any SDL Events (this returns the first element in a queue)
    if (SDL_PollEvent(&_event))
	{
        //Determine the type of the event
        switch(_event.type)
		{
        
            //User has clicked the close button
            case SDL_QUIT:
                return InputManager::QUIT;

            //User has pressed a keyboard key - single stroke
            case SDL_KEYDOWN:
			/*
				cout << "in key down" << endl;

				for (vector<InputWord*>::iterator it = input_words.begin(); it!=input_words.end(); ++it) 
				{
					if((*it)->get_listen_to_KeyStroke() == true)
					{
						inputEvent = (*it)->update(_event);
						//cout << "bla bla bla" << endl;
						if(inputEvent->get_eventHasOccured() == true)
							{
								input_events.push_back(inputEvent);
							}
					}

					if((*it)->get_listen_to_KeyState() == true)
					{
						inputEvent = (*it)->update(_event);
						//cout << "bla bla bla" << endl;
						if(inputEvent->get_eventHasOccured() == true)
							{
								input_events.push_back(inputEvent);
							}
					}
				}
				*/
                break;

			//User has pressed a keyboard key - single stroke
            case SDL_KEYUP:
			/*
				cout << "in key up" << endl;

				for (vector<InputWord*>::iterator it = input_words.begin(); it!=input_words.end(); ++it) 
				{
					if((*it)->get_listen_to_KeyState() == true)
					{
						inputEvent = (*it)->update(_event);
						//cout << "bla bla bla" << endl;
						if(inputEvent->get_eventHasOccured() == true)
							{
								input_events.push_back(inputEvent);
							}
					}
				}
				*/
                break;
				
            //User has moved the mouse
            case SDL_MOUSEMOTION:

				//cout << "mouse motion" << endl;

				for (vector<InputWord*>::iterator it = input_words.begin(); it!=input_words.end(); ++it) 
				{
					
					if((*it)->get_listen_to_MouseMovement() == true)
					{
						cout << " . " << endl;
						//cout << "type:" << typeid(it).name() << endl;

						//cout << "type in IM of IW:" << typeid(&(*it)).name() << endl;
						InputWord * vp = dynamic_cast<InputWord *>(*it);
						//cout << "type in IM of IW:" << typeid(vp).name() << endl;
												
						MouseMovementInputWord * hp = dynamic_cast<MouseMovementInputWord *>(*it);
						//cout << "type in IM of IW:" << typeid(hp).name() << endl;

						inputEvent = (*it)->update(_event);

						if(inputEvent->get_eventHasOccured() == true)
							{
								input_events.push_back(inputEvent);
								cout << "..." << endl;
							}
					}
				}
                break;
                
            //User has pressed one of the buttons (single click register)
            case SDL_MOUSEBUTTONDOWN:
				/*
				for (vector<InputWord*>::iterator it = input_words.begin(); it!=input_words.end(); ++it) 
				{
					if((*it)->get_listen_to_MouseSingleClick() == true)
					{
						inputEvent = (*it)->update(_event);
						//cout << "bla bla bla" << endl;
						if(inputEvent->get_eventHasOccured() == true)
							{
								input_events.push_back(inputEvent);
							}
					}

					if((*it)->get_listen_to_MouseButtonPressed() == true)
					{
						inputEvent = (*it)->update(_event);
						//cout << "bla bla bla" << endl;
						if(inputEvent->get_eventHasOccured() == true)
							{
								input_events.push_back(inputEvent);
							}
					}
				}
				*/
                break;

			case SDL_MOUSEBUTTONUP:
				/*
				for (vector<InputWord*>::iterator it = input_words.begin(); it!=input_words.end(); ++it) 
				{
					if((*it)->get_listen_to_MouseButtonPressed() == true)
					{
						inputEvent = (*it)->update(_event);
						//cout << "bla bla bla" << endl;
						if(inputEvent->get_eventHasOccured() == true)
							{
								input_events.push_back(inputEvent);
							}
					}
				}
				*/
                break;

			//Joystick axis motion
			case SDL_JOYAXISMOTION:
				break;

			// Joystick trackball motion
			case SDL_JOYBALLMOTION:
				break;

			// Joystick hat motion
			case SDL_JOYHATMOTION:
				break;

			// Joystick button
			case SDL_JOYBUTTONUP:			
				break;
			
			// Joystick button
			case SDL_JOYBUTTONDOWN:			
				break;

			// Window resize
			case SDL_VIDEORESIZE:
				break;

			case SDL_VIDEOEXPOSE:
				break;

            //None of the above types have happened
            default: 
                break;
		}

		return InputManager::NORMAL;
	}
}