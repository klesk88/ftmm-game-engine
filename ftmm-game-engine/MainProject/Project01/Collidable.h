#ifndef __Collidable_h__
#define __Collidable_h__

#include "GameObject.h"
#include "Matrix4.h"

class Collidable
{
	public:
		void raise(int n_value);
		Collidable(GameObject* object_attached);
		void drawBoundingBox();
		void getBoundingBoxPoint(int index);


	private:
		__event void MyEvent(int n_value);

		void setOrientedBoundingBox();
		void setTransformationAtOBB();
		void stampMatrix();

		Vector3* m_bounding_box;
		Vector3* m_bounding_box_trans;
		//TransformNode* m_transform_node;
		GameObject* m_object_attached;
		Matrix4 tranform_matrix;
		


};


#endif