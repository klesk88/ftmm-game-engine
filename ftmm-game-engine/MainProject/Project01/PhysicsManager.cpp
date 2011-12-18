#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::m_instance = nullptr;

PhysicsManager::PhysicsManager()
{
	SceneManager * sc_mn = SceneManager::getInstance();
	m_transform_node =  sc_mn->getRootTransformNode()->createChild("PhysicsNode", Vector3::ZERO);
	m_gjk = GJK::getInstance();
	count = 0;
	collision = false;
}

PhysicsManager* PhysicsManager::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new PhysicsManager();
	}

	return m_instance;
}

void PhysicsManager::removeCollidable(Collidable * coll_ptr)
{
	m_transform_node->attached_collidable.remove(coll_ptr);
}

Collidable* PhysicsManager::attachCollidable(GameObject* game_obj)
{
	Collidable * mCollidable = new (EAllocationType::PHYSICS) Collidable(game_obj);
	m_transform_node->attachCollidable(mCollidable);
	return mCollidable;
}

TransformNode* PhysicsManager::getPhysicTransformNode()
{
	return m_transform_node;
}

std::list<GameObject*> PhysicsManager::collisionDetector()
{
	std::list<Collidable*>::iterator iter;
	std::list<Collidable*>::iterator iter2;
	std::list<Collidable*>* coll_list = m_transform_node->getAttachedCollidablePtr();

	std::list<GameObject*> object_collided;
	//for(iter=coll_list->begin(); iter != coll_list->end(); iter++)
	//{
	//	(*iter)->setTransformationAtOBB();
	//}

	for(iter=coll_list->begin(); iter != coll_list->end(); iter++)
	{
		//to create OBB in the first element
		if(iter==coll_list->begin())
		{
			(*iter)->setTransformationAtOBB();
		}

		iter2 = iter;
		iter2++;
		for(; iter2 != coll_list->end(); iter2++)
		{
			//to create OBB in others elements only in the first cilcle
			if(iter==coll_list->begin())
			{
				(*iter2)->setTransformationAtOBB();
			}

			//Control if there is some collision
			if(m_gjk->bodiesIntersect((*iter),(*iter2)))
			{
				object_collided.push_back((*iter)->getGameObject());
				object_collided.push_back((*iter2)->getGameObject());
				if(!collision)
				{
					std::cout << "collision" << std::endl;
					collision = true;
				}
			}
			else
			{
				if(collision)
				{
					std::cout << "NOT   collision" << std::endl;
					collision = false;
				}
			}
		}
	}


	return object_collided;
}