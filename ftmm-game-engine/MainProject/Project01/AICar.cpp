#include "AICar.h"
#include "GameObject.h"
#include "AI_Manager.h"

AICar::AICar(){}

/*
CubeObjectTest::CubeObjectTest(string name, Vector3 position, Quaternion orientation) : GameObject(name, position, orientation)
{

}
*/

AICar::~AICar()
{
	TransformNode * parent = mTransformNode->getParent();
	parent->deleteChild(mTransformNode);
	mCollidable->~Collidable();
	MemoryManagement::operator delete (mCollidable,EAllocationType::NO_ASSIGNED) ;
}

void AICar::init(int code)
{
	mMesh = ResourceManager::getInstance()->loadMesh("Data/car.obj");
	mTransformNode->attachObject(mMesh);
	mCollidable = PhysicsManager::getInstance()->attachCollidable(this);
	mAgent = AI_Manager::getInstance()->get_AIAgent(1);
};