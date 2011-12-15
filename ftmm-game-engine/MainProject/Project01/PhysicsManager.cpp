#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::m_instance = nullptr;

PhysicsManager::PhysicsManager()
{
	SceneManager * sc_mn = SceneManager::getInstance();
	m_transform_node =  sc_mn->getRootTransformNode()->createChild("PhysicsNode", Vector3::ZERO);

}

PhysicsManager* PhysicsManager::getInstance()
{
	if(m_instance == NULL)
	{
	
		m_instance = new PhysicsManager();

	}

	return m_instance;
}

void PhysicsManager::attachCollidable(Collidable * coll_ptr)
{
	m_transform_node->attachCollidable(coll_ptr);
}

TransformNode* PhysicsManager::getPhysicTransformNode()
{
	return m_transform_node;
}