#ifndef FourDirectionsMovement_InputEvent_H
#define FourDirectionsMovement_InputEvent_H

#include "InputEvent.h"

class FourDirectionsMovement_InputEvent: public InputEvent 
{
private:
	bool north;
	bool east;
	bool south;
	bool west;

public:
	FourDirectionsMovement_InputEvent() : InputEvent()
	{
		eventHasOccured = false;
	}

	bool get_north() {return north;}
	void set_north(bool pass) {north = pass;}
	bool get_east() {return east;}
	void set_east(bool pass) {east = pass;}
	bool get_south() {return south;}
	void set_south(bool pass) {south = pass;}
	bool get_west() {return west;}
	void set_west(bool pass) {west = pass;}


};

#endif