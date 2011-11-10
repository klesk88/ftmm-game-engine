#include "CubeObjectTest.h"

CubeObjectTest::CubeObjectTest(){}

/*
CubeObjectTest::CubeObjectTest(string name, Vector3 position, Quaternion orientation) : GameObject(name, position, orientation)
{

}
*/

void CubeObjectTest::init()
{
	mMesh = new Mesh(0.4,1.0,0.0,0.0);
	mTransformNode->attachObject(mMesh);
		//cube = new Mesh(0.4,1.0,0.0,0.0);
		//cube2 = new Mesh(0.3,0.0,0.0,1.0);
		//cube3 = new Mesh(0.2,0.0,1.0,0.0);
		//cube4 = new Mesh(0.3,0.5,0.0,0.5);
	};