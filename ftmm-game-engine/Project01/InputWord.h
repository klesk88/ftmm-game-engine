#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include "InputEvent.h"

using namespace std;

#ifndef InputWord_H
#define InputWord_H


class InputWord
{
protected:

	SDL_Event event_current;

	// Is this Input Event true?
	bool event_is_true;
	// Use this e.g. to return how much a mouse has been moved
	float value_of_event;

	bool listen_to_KeyStroke; 
	bool listen_to_KeyState;
	bool listen_to_MouseSingleClick;
	bool listen_to_MouseButtonPressed;
	bool listen_to_MouseMovement;

	// In which game states is this input event supposed to be true
	bool true_in_gameStates; //This should be an array of the same size as gameState enum, so that the enum_value refers to the position
							// in the array...
	// Set to true if this Input handling should occur in every game state
	bool true_in_all_gameStates; //this speeds up gameState truth queries and can make it easier to manage input words

public:

	// this virtual makes this class a polymorphic class
	virtual InputEvent* update(SDL_Event _event)
	{
		// This returns an empty and meaningless event
		// think of something better to do here
		event_current = _event;
		InputEvent * defaultEvent = new InputEvent() ;
		return defaultEvent;
	}
	InputWord(int count_gameStates)
	{
		listen_to_KeyStroke=false;
		listen_to_KeyState=false;
		listen_to_MouseSingleClick=false;
		listen_to_MouseButtonPressed=false;
		listen_to_MouseMovement=false;
	}

	bool get_listen_to_KeyStroke() {return listen_to_KeyStroke;} //These are for InputManager to understand which instances to update
	bool get_listen_to_KeyState() {return listen_to_KeyState;}
	bool get_listen_to_MouseSingleClick() {return listen_to_MouseSingleClick;}
	bool get_listen_to_MouseButtonPressed() {return listen_to_MouseButtonPressed;}
	bool get_listen_to_MouseMovement() {return listen_to_MouseMovement;}

	void set_listen_to_KeyStroke(bool value) {listen_to_KeyStroke = value;}
	void set_listen_to_KeyState(bool value) {listen_to_KeyState = value;}
	void set_listen_to_MouseSingleClick(bool value) {listen_to_MouseSingleClick = value;}
	void set_listen_to_MouseButtonPressed(bool value) {listen_to_MouseButtonPressed = value;}
	void set_listen_to_MouseMovement(bool value) {listen_to_MouseMovement = value;}

	//---------------------------------------------------------------------------
	// Game state management
	//---------------------------------------------------------------------------
	//Add a game state in which this should be true
	//game states are false by default.
	void add_GameStateCondition(int enum_value_of_gamestate);
	//Add a game state in which this should be false
	void remove_GameStateCondition(int enum_value_of_gamestate);
	// This inputEvent is valid for all game states
	void set_all_GameStateCondition(bool false_or_true);
	//get the game states for which it is true
	bool check_GameState_Condition(int enum_value_of_gamestate);
	//----------------------------------------------------------------------------
};

#endif