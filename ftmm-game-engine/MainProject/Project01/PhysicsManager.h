#ifndef PhysicsManager_H
#define PhysicsManager_H

#include "TransformNode.h"
#include "SceneManager.h"
#include "Collidable.h"

#pragma once //singletone

class PhysicsManager
{

	public:
		static PhysicsManager * getInstance ();
		void attachCollidable(Collidable * coll_ptr);
		TransformNode* getPhysicTransformNode();

	private:
		PhysicsManager();
		static PhysicsManager * m_instance;
		
		TransformNode* m_transform_node;

};

#endif