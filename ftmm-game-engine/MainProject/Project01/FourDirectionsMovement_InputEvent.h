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

	float x_velocity;
	float y_velocity;

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

	float get_x_velocity() {return x_velocity;}
	void set_x_velocity(float pass) {x_velocity = pass;}
	float get_y_velocity() {return y_velocity;}
	void set_y_velocity(float pass) {y_velocity= pass;}


};

#endif