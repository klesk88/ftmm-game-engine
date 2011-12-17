#ifndef PhysicsManager_H
#define PhysicsManager_H

#include "TransformNode.h"
#include "SceneManager.h"
#include "Collidable.h"
#include "GJK.h"
#include "RigidBody.h"
#include "Prova.h"



#pragma once

class PhysicsManager
{

	public:
		static PhysicsManager * getInstance ();
		void attachCollidable(Collidable * coll_ptr);
		TransformNode* getPhysicTransformNode();
		void collisionDetector();
		void removeCollidable(Collidable * coll_ptr);

	private:
		PhysicsManager();
		static PhysicsManager * m_instance;
		
		GJK* m_gjk;
		//Prova* prova;
		TransformNode* m_transform_node;
		int count;
};

#endif