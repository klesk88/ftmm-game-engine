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
	CameraMovementInputWord* cameraMotion = new CameraMovementInputWord(0);
	cameraMotion->set_listen_to_MouseMovement(true);
	input_words.push_back(cameraMotion);
	cout << "type in IM of IW:" << typeid(cameraMotion).name() << endl;

	FourDirectionsMovement_InputWord* fourDirectionalMovement = new FourDirectionsMovement_InputWord(0);
	fourDirectionalMovement->set_listen_to_KeyState(true);
	input_words.push_back(fourDirectionalMovement);
	cout << "type in IM of IW:" << typeid(fourDirectionalMovement).name() << endl;
	
}

InputManager * InputManager::m_instance = NULL;

InputManager * InputManager::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new InputManager();
	}
	return m_instance;
}



// makes a coarse pre-selection on which InputWords to update, goes into the case which handles the current input and then iterates through 
// the vector containing the Input word (bot operations have O(n)). This is faster than updating every vector (already O(n) for calling).
InputManager::SIGNAL InputManager::handle_input()
{

	input_events.clear();

    //Poll to see if we have any SDL Events (this returns the first element in a queue)
    while (SDL_PollEvent(&_event))
	{
        //Determine the type of the event
        switch(_event.type)
		{
        
            //User has clicked the close button
            case SDL_QUIT:
                return InputManager::QUIT;

            //User has pressed a keyboard key - single stroke
            case SDL_KEYDOWN:
			
				//cout << "in key down" << endl;

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


                break;

			//User has pressed a keyboard key - single stroke
            case SDL_KEYUP:
			
				
				//cout << "in key up" << endl;

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
				
                break;
				
            //User has moved the mouse
            case SDL_MOUSEMOTION:
			
				// iterate through all Input words to see which input words should be updated
				for (vector<InputWord*>::iterator it = input_words.begin(); it!=input_words.end(); ++it) 
				{
					// current input word interested in mouse movement?
					if((*it)->get_listen_to_MouseMovement() == true)
					{
						// get an event from the update method
						inputEvent = (*it)->update(_event);
						// if the event is interesting, store it so others can request it from the InputManager
						if(inputEvent->get_eventHasOccured() == true)
							{
								input_events.push_back(inputEvent);
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
	}
	return InputManager::NORMAL;
}