#include "CubeObjectTest.h"

//#include "PhysicsManager.h"

CubeObjectTest::CubeObjectTest(){}

/*
CubeObjectTest::CubeObjectTest(string name, Vector3 position, Quaternion orientation) : GameObject(name, position, orientation)
{

}
*/

CubeObjectTest::~CubeObjectTest()
{
	TransformNode * parent = mTransformNode->getParent();
	parent->deleteChild(mTransformNode);
	delete mCollidable;
}

void CubeObjectTest::init(int code)
{
	switch(code)
	{
		case 1:
			mMesh = ResourceManager::getInstance()->loadMesh("Data/car.obj");
			mTransformNode->attachObject(mMesh);
			mCollidable = new Collidable(this);
			PhysicsManager::getInstance()->attachCollidable(mCollidable);
			break;
		case 2:
			//mMesh = ResourceManager::getInstance()->loadMesh("Data/.obj");
			mMesh = new Mesh(0.4f,1.0f,0.0f,0.0f);
			mCollidable = new Collidable(this);
			mTransformNode->attachObject(mMesh);
			break;
		case 3:
			mMesh = ResourceManager::getInstance()->loadMesh("Data/SphereAndCube.obj");
			mTransformNode->attachObject(mMesh);
			mCollidable = new Collidable(this);
			PhysicsManager::getInstance()->attachCollidable(mCollidable);
			break;
	}
	//mMesh = new Mesh(0.4,1.0,0.0,0.0);
	//mTransformNode->attachObject(mMesh);
		//cube = new Mesh(0.4,1.0,0.0,0.0);
		//cube2 = new Mesh(0.3,0.0,0.0,1.0);
		//cube3 = new Mesh(0.2,0.0,1.0,0.0);
		//cube4 = new Mesh(0.3,0.5,0.0,0.5);
};

//void CubeObjectTest::destroy()
//{
//	TransformNode * parent = mTransformNode->getParent();
//	parent->deleteChild(mTransformNode);
//	delete mCollidable;
//}