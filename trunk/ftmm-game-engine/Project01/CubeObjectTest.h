#ifndef CubeObjectTest_H
#define CubeObjectTest_H
//#include "GameObject.h"
//#include "Object3D.h"
//#ifndef  Object3d_H
//#define Object3d_H
//#endif

#include "Object3D.h"
#include "GameObject.h"
#include "Quaternion.h"
#include "Vector3.h"
#include <string>
using namespace::std;

#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX Why is Object3D not included here?")

class CubeObjectTest : GameObject, Object3D/*: public Object3D, public GameObject*/
{

//private:
public:
#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX CubeObjectTest included")
	CubeObjectTest();
	CubeObjectTest(string name, Vector3 position, Quaternion orientation);


	void update(vector<Event*> events){};
};

#endif
