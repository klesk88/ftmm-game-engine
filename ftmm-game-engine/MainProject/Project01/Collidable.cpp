#include "Collidable.h"

Collidable::Collidable(GameObject* object_attached)
{
	m_object_attached = object_attached;
	//m_transform_node = m_object_attached->mTransformNode;
	m_bounding_box = new Vector3[8];
	setOrientedBoundingBox();
}

void Collidable::raise (int n_value)
{ 
	__raise MyEvent(n_value);
}

void Collidable::setOrientedBoundingBox()
{
	Vector3 min = Vector3(99999.0f,99999.0f,99999.0f);
	Vector3 max = Vector3(-99999.0f,-99999.0f,-99999.0f);
	Vector3* temp_vertices;
	int count_vertices = 0;

	if( m_object_attached->mMesh->hasSubMesh())
	{
		std::map<std::string, Mesh*>::iterator iter;
		for(iter = m_object_attached->mMesh->sub_mesh_tab.begin();  iter != m_object_attached->mMesh->sub_mesh_tab.end(); ++iter)
		{
			count_vertices += iter->second->getNumVertices();
		}
		temp_vertices = new Vector3[count_vertices];

		int k=0;
		for(iter = m_object_attached->mMesh->sub_mesh_tab.begin();  iter != m_object_attached->mMesh->sub_mesh_tab.end(); ++iter)
		{
			Vector3* temp_sub_mesh_vertices = iter->second->getVertices();
			for(int i=0; i < iter->second->getNumVertices(); i++)
			{
				temp_vertices[k] = temp_sub_mesh_vertices[i];
				k++;
			}
		}

	}
	else
	{
		temp_vertices = m_object_attached->mMesh->getVertices();
	}

	Vector3 item;
	for (int i = 0; i< count_vertices; i++)
	{
		item = temp_vertices[i];
		if(item.x < min.x)
			min.x = item.x;
		if(item.y < min.y)
			min.y = item.y;
		if(item.z < min.z)
			min.z = item.z;

		if(item.x > max.x)
			max.x = item.x;
		if(item.y > max.y)
			max.y = item.y;
		if(item.z > max.z)
			max.z = item.z;
	}


	m_bounding_box[0].x = min.x;
	m_bounding_box[0].y = min.y;
	m_bounding_box[0].z = min.z;

	m_bounding_box[1].x = max.x;
	m_bounding_box[1].y = min.y;
	m_bounding_box[1].z = min.z;

	m_bounding_box[2].x = max.x;
	m_bounding_box[2].y = min.y;
	m_bounding_box[2].z = max.z;

	m_bounding_box[3].x = min.x;
	m_bounding_box[3].y = min.y;
	m_bounding_box[3].z = max.z;

	m_bounding_box[4].x = min.x;
	m_bounding_box[4].y = max.y;
	m_bounding_box[4].z = min.z;

	m_bounding_box[5].x = max.x;
	m_bounding_box[5].y = max.y;
	m_bounding_box[5].z = min.z;

	m_bounding_box[6].x = max.x;
	m_bounding_box[6].y = max.y;
	m_bounding_box[6].z = max.z;

	m_bounding_box[7].x = min.x;	
	m_bounding_box[7].y = max.y;
	m_bounding_box[7].z = max.z;

}

void Collidable::drawBoundingBox()
{
	glBegin(GL_LINES);
	glColor3f(1.0,0.0,0.0);

	glVertex3f(m_bounding_box[0].x,m_bounding_box[0].y,m_bounding_box[0].z);
	glVertex3f(m_bounding_box[1].x,m_bounding_box[1].y,m_bounding_box[1].z);

	glVertex3f(m_bounding_box[1].x,m_bounding_box[1].y,m_bounding_box[1].z);
	glVertex3f(m_bounding_box[2].x,m_bounding_box[2].y,m_bounding_box[2].z);

	glVertex3f(m_bounding_box[2].x,m_bounding_box[2].y,m_bounding_box[2].z);
	glVertex3f(m_bounding_box[3].x,m_bounding_box[3].y,m_bounding_box[3].z);

	glVertex3f(m_bounding_box[3].x,m_bounding_box[3].y,m_bounding_box[3].z);
	glVertex3f(m_bounding_box[0].x,m_bounding_box[0].y,m_bounding_box[0].z);

	glVertex3f(m_bounding_box[4].x,m_bounding_box[4].y,m_bounding_box[4].z);
	glVertex3f(m_bounding_box[5].x,m_bounding_box[5].y,m_bounding_box[5].z);

	glVertex3f(m_bounding_box[5].x,m_bounding_box[5].y,m_bounding_box[5].z);
	glVertex3f(m_bounding_box[6].x,m_bounding_box[6].y,m_bounding_box[6].z);

	glVertex3f(m_bounding_box[6].x,m_bounding_box[6].y,m_bounding_box[6].z);
	glVertex3f(m_bounding_box[7].x,m_bounding_box[7].y,m_bounding_box[7].z);

	glVertex3f(m_bounding_box[7].x,m_bounding_box[7].y,m_bounding_box[7].z);
	glVertex3f(m_bounding_box[4].x,m_bounding_box[4].y,m_bounding_box[4].z);

	glVertex3f(m_bounding_box[0].x,m_bounding_box[0].y,m_bounding_box[0].z);
	glVertex3f(m_bounding_box[4].x,m_bounding_box[4].y,m_bounding_box[4].z);

	glVertex3f(m_bounding_box[1].x,m_bounding_box[1].y,m_bounding_box[1].z);
	glVertex3f(m_bounding_box[5].x,m_bounding_box[5].y,m_bounding_box[5].z);

	glVertex3f(m_bounding_box[2].x,m_bounding_box[2].y,m_bounding_box[2].z);
	glVertex3f(m_bounding_box[6].x,m_bounding_box[6].y,m_bounding_box[6].z);

	glVertex3f(m_bounding_box[3].x,m_bounding_box[3].y,m_bounding_box[3].z);
	glVertex3f(m_bounding_box[7].x,m_bounding_box[7].y,m_bounding_box[7].z);

	glEnd();
}