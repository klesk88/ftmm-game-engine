#ifndef __Object3D_H
#define __Object3D_H

//#include "GameObject.h"
#include "TransformNode.h"
#include "SceneManager.h"


class Object3D// : public GameObject
{
private:
	TransformNode* m_transformNode;
	
public:
	
	Object3D(Vector3 position, Quaternion orientation); //: public GameObject();
	//virtual void update(vector<Event*> events);
};

#endif

