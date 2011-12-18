#include "PlayerCar.h"
#include "CarMovement_InputEvent.h"


PlayerCar::PlayerCar(){}

/*
CubeObjectTest::CubeObjectTest(string name, Vector3 position, Quaternion orientation) : GameObject(name, position, orientation)
{

}
*/

PlayerCar::~PlayerCar()
{
	TransformNode * parent = mTransformNode->getParent();
	parent->deleteChild(mTransformNode);
	delete mCollidable;
}

void PlayerCar::init()
{
	speed = 0.02;
	mMesh = ResourceManager::getInstance()->loadMesh("Data/car.obj");
	mTransformNode->attachObject(mMesh);
	mCollidable = new Collidable(this);
	PhysicsManager::getInstance()->attachCollidable(mCollidable);
}

//void PlayerCar::destroy()
//{
//	TransformNode * parent = mTransformNode->getParent();
//	parent->deleteChild(mTransformNode);
//	delete mCollidable;
//}

void PlayerCar::update()
{
	Matrix3 * mt3 = new Matrix3;
	*mt3 = mTransformNode->getLocalAxes();

	mTransformNode->translate((mt3->getColumn(0) * speed),MovableObject::TransformSpace::TS_WORLD);
}

void PlayerCar::handleInput(CarMovement_InputEvent* inpEvt)
{
	Matrix3 * mt3 = new Matrix3;
	*mt3 = mTransformNode->getLocalAxes();

	if (inpEvt->get_x_velocity() != 0)
	{
		mTransformNode->translate((mt3->getColumn(2) * inpEvt->get_x_velocity() * 3),MovableObject::TransformSpace::TS_WORLD);
		
	}
	if (inpEvt->get_y_velocity() != 0)
	{
		speed = speed + (inpEvt->get_y_velocity()*-0.01);
	}
}