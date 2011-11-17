#include "CubeObjectTest.h"
#include "ResourceManager.h"
CubeObjectTest::CubeObjectTest(){}

/*
CubeObjectTest::CubeObjectTest(string name, Vector3 position, Quaternion orientation) : GameObject(name, position, orientation)
{

}
*/

void CubeObjectTest::init(int code)
{
	switch(code)
	{
		case 1:
			mMesh = ResourceManager::getInstance()->loadMesh("Data/car2.obj");
			mTransformNode->attachObject(mMesh);
			cout << "case 1" << endl;
			break;
		case 2:
			mMesh = new Mesh(0.4,1.0,0.0,0.0);
			mTransformNode->attachObject(mMesh);
			cout << "case 2" << endl;
			break;
	}
	//mMesh = new Mesh(0.4,1.0,0.0,0.0);
	//mTransformNode->attachObject(mMesh);
		//cube = new Mesh(0.4,1.0,0.0,0.0);
		//cube2 = new Mesh(0.3,0.0,0.0,1.0);
		//cube3 = new Mesh(0.2,0.0,1.0,0.0);
		//cube4 = new Mesh(0.3,0.5,0.0,0.5);
	};