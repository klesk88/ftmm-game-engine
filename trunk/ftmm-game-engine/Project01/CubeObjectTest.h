#ifndef __CubeObjectTest_H
#define __CubeObjectTest_H

#include "Object3D.h"
#include "GameObject.h"

class CubeObjectTest : public GameObject : public Object3D
{
private:
public:
	CubeObjectTest(string name, Vector3 position, Quaterion orientation) : GameObject(name) : Object3D(position, orientation)
};

#endif