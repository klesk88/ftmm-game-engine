#ifndef __GameObject_H__
#define __GameObject_H__

#include "event.h"
#include <vector>
#include <string>

using namespace std;

class GameObject
{
private:
	string name_this;

public:
	// Specify exactly one transfrom node if you want to include this into the SceneGraph

	GameObject(string name)
	{
		name_this = name;
		// If Game Object should be part of SceneGraph do something like this:
		// TransformNode tn = SceneManager::getInstance()->getRootTransformNode()->createChild("node6");
	}

	virtual void update(vector<Event*> events);
};

#endif

