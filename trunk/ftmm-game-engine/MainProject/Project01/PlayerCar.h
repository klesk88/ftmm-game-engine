#ifndef PlayerCar_H
#define PlayerCar_H


#include "IObject3D.h"
#include "GameObject.h"
#include "Quaternion.h"
#include "Vector3.h"
#include <string>
using namespace::std;

class CarMovement_InputEvent;

class PlayerCar : public GameObject
{
private:
	float speed;

public:
#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX PlayerCarincluded")
	PlayerCar();
	PlayerCar(string name, Vector3 position = Vector3::ZERO, Quaternion orientation = Quaternion::IDENTITY) : GameObject(name, position, orientation){};

	void init();
	void destroy();
	
	// as in this example the level preselects events, 
	// there is also an update method that is called without arguments
	void update();
	
	void update(vector<Event*> events){};

	//implementing this method specifically for a single InputWord 
	//is a decision of the engine user.
	void handleInput(CarMovement_InputEvent* inpEvt);
};

#endif
