// good article: http://www.gamedev.net/blog/355/entry-2250186-designing-a-robust-input-handling-system-for-games/
// maybe interesting: http://dominikgrabiec.com/category/gamedev/
// sdl documentation: http://www.libsdl.org/docs/html/eventstructures.html

/*
    Returns:    Input_Manager::SIGNAL enumeration:
                    NORMAL - on normal loop returns
                    QUIT   - on request for program termination
*/
#ifndef InputManager_H
#define InputManager_H

#include <vector>
#include "InputWord.h"
#include "MouseMovementInputWord.h"

using namespace std;

class InputManager
{
public:

    /*  Here we define the signals we need to let our parent know the status
        of the program. */
    enum SIGNAL{
        NORMAL,     //handle_input() processed input correctly
        QUIT        //handle_input() says the user wants to exit the program
    };

	InputManager();
	~InputManager(){};

/*  General function called to interpret all user input. 
    Returns Input_Manager::NORMAL on normal loop returns
            Input_Manager::QUIT when user requests to quit.  */
    SIGNAL handle_input();
    
	vector<Event*> get_input_events()
		{	return input_events;}

protected:

	InputEvent* inputEvent;

	bool mouse_button_currently_pressed;

	vector<InputWord*> input_words;

	vector<Event*> input_events;

private:

    /*  SDL Event that contains the input device data from the last query  */
    SDL_Event _event;
    
};
#endif
