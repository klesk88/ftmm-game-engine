#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::m_instance = nullptr;

PhysicsManager::PhysicsManager()
{
	SceneManager * sc_mn = SceneManager::getInstance();
	m_transform_node =  sc_mn->getRootTransformNode()->createChild("PhysicsNode", Vector3::ZERO);
	m_gjk = GJK::getInstance();
//	prova = new Prova();
	count = 0;
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

void PhysicsManager::attachCollidable(Collidable * coll_ptr)
{
	m_transform_node->attachCollidable(coll_ptr);
}

TransformNode* PhysicsManager::getPhysicTransformNode()
{
	return m_transform_node;
}

void PhysicsManager::collisionDetector()
{
	std::list<Collidable*>::iterator iter;
	std::list<Collidable*>::iterator iter2;
	std::list<Collidable*>* coll_list = m_transform_node->getAttachedCollidablePtr();

	for(iter=coll_list->begin(); iter != coll_list->end(); iter++)
	{
		(*iter)->setTransformationAtOBB();
	}


	for(iter=coll_list->begin(); iter != coll_list->end(); iter++)
	{
		iter2 = iter;
		iter2++;
		for(; iter2 != coll_list->end(); iter2++)
		{
			if(m_gjk->bodiesIntersect((*iter),(*iter2)))
			//if(prova->bodiesIntersect((*iter),(*iter2)))
			{
				std::cout << "collision" << std::endl;
			}
			else
			{
				//std::cout << "NOT   collision" << std::endl;
			}
		}
	}
}