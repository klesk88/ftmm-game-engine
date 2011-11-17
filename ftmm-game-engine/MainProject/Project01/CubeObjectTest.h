#ifndef CubeObjectTest_H
#define CubeObjectTest_H
//#include "GameObject.h"
//#include "Object3D.h"
//#ifndef  Object3d_H
//#define Object3d_H
//#endif

#include "IObject3D.h"
#include "GameObject.h"
#include "Quaternion.h"
#include "Vector3.h"
#include <string>
using namespace::std;

#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX Why is Object3D not included here?")

class CubeObjectTest : public GameObject//, IObject3D/*: public Object3D, public GameObject*/
{

//private:
public:
#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX CubeObjectTest included")
	CubeObjectTest();
	CubeObjectTest(string name, Vector3 position = Vector3::ZERO, Quaternion orientation = Quaternion::IDENTITY) : GameObject(name, position, orientation){};

	void init(int code);
		/*
	{
		mMesh = new Mesh(0.4,1.0,0.0,0.0);
		mTransformNode->attachObject(mMesh);
		//cube = new Mesh(0.4,1.0,0.0,0.0);
		//cube2 = new Mesh(0.3,0.0,0.0,1.0);
		//cube3 = new Mesh(0.2,0.0,1.0,0.0);
		//cube4 = new Mesh(0.3,0.5,0.0,0.5);
	};
	*/
	void update(vector<Event*> events){};
};

#endif
