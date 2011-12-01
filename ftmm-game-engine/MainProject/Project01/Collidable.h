#ifndef __Collidable_h__
#define __Collidable_h__

#include "GameObject.h"

class Collidable
{
	public:
		void raise(int n_value);
		Collidable(GameObject* object_attached);
		void drawBoundingBox();


	private:
		__event void MyEvent(int n_value);

		void setOrientedBoundingBox();

		Vector3* m_bounding_box;
		//TransformNode* m_transform_node;
		GameObject* m_object_attached;
		


};


#endif