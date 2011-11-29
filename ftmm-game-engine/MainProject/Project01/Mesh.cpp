#define NO_SDL_GLEXT
#include <GL\glew.h>
#include "Mesh.h"

#include <iostream>

using namespace std;

int Mesh::num_name = 0;

//New Version
Mesh::Mesh(std::string name)
{
	//m_name = name;
	m_name = num_name;
	num_name +=1;

	vector_buffer_obj = NULL;
	index_buffer = NULL;
	normal_buffer = NULL;
	binormal_buffer = NULL;
	tangent_buffer = NULL;
	texture_coord_buffer = NULL;

	m_num_faces = 0;
	m_num_vertices = 0;
	m_num_indices = 0;

	sub_mesh_tab.clear();
}

Mesh::~Mesh()
{
	if(vector_buffer_obj != NULL)
	{
		glDeleteBuffers(1, &vector_buffer_obj);
	}
	if(index_buffer != NULL)
	{
		glDeleteBuffers(1, &index_buffer);
	}
	if(normal_buffer != NULL)
	{
		glDeleteBuffers(1, &normal_buffer);
	}
	if(binormal_buffer != NULL)
	{
		glDeleteBuffers(1, &binormal_buffer);
	}
	if(tangent_buffer != NULL)
	{
		glDeleteBuffers(1, &tangent_buffer);
	}
	if(texture_coord_buffer != NULL)
	{
		glDeleteBuffers(1, &texture_coord_buffer);
	}
}

void Mesh::addSubMesh(Mesh* sub_mesh)
{
	sub_mesh_tab.insert(std::pair<std::string, Mesh *>(sub_mesh->m_name, sub_mesh));
}

void Mesh::initBuffer()
{
	//glGenVertexArrays(1,&VAO);
	//glBindVertexArray(VAO);
 
	glGenBuffers(1, &vector_buffer_obj);
  	glBindBuffer(GL_ARRAY_BUFFER, vector_buffer_obj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_num_vertices, &m_vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_num_indices, &m_indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normal_buffer);
  	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_num_vertices, &m_normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &binormal_buffer);
  	glBindBuffer(GL_ARRAY_BUFFER, binormal_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_num_vertices, &m_binormals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &tangent_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, tangent_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_num_vertices, &m_tangents[0], GL_STATIC_DRAW);

	glGenBuffers(1, &texture_coord_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, texture_coord_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_num_vertices, &m_texture_coord[0], GL_STATIC_DRAW);
}

bool Mesh::hasSubMesh()
{
	if(sub_mesh_tab.empty())
		return false;
	else
		return true;
}

void Mesh::renderMesh()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
	glEnableVertexAttribArray(tangents_attrib_array);
	glEnableVertexAttribArray(binormals_attrib_array);

	//Vertices
	glBindBuffer(GL_ARRAY_BUFFER, vector_buffer_obj);
    glVertexPointer(3, GL_FLOAT, 0, 0);
	//Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	//Normals
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
	glNormalPointer(GL_FLOAT, 0, 0);
	//Binormals
	glBindBuffer(GL_ARRAY_BUFFER, binormal_buffer);
	glVertexAttribPointer(binormals_attrib_array, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//Tangents
	glBindBuffer(GL_ARRAY_BUFFER, tangent_buffer);
	glVertexAttribPointer(tangents_attrib_array, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//Texture Coords
	glBindBuffer(GL_ARRAY_BUFFER, texture_coord_buffer);
	glTexCoordPointer(3, GL_FLOAT, 0, NULL);
	
	//Draw
    glPushMatrix();
	glColor3f(153.0f,0.0f,102.0f);
    glDrawElements(GL_TRIANGLES, m_num_indices, GL_UNSIGNED_INT, 0);
    glPopMatrix();

	//Free Buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
	glDisableVertexAttribArray(tangents_attrib_array);
	glDisableVertexAttribArray(binormals_attrib_array);

}

void Mesh::renderMeshDirect()
{
	//Draw Line
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f,1.0f,0);
	for(int i=0; i<m_num_indices; i++)
	{
		int index = m_indices[i];
		glVertex3f(m_vertices[index].x,m_vertices[index].y,m_vertices[index].z);
	}

	glEnd();
	glPopMatrix();
}

Vector3* Mesh::getVertices()
{
	return m_vertices;
}

Vector3* Mesh::getNormals()
{
	return m_normals;
}

Vector3* Mesh::getBinormals()
{
	return m_binormals;
}

Vector3* Mesh::getTangents()
{
	return m_tangents;
}


//old Version
//constructor temporily in header file

void Mesh::drawCube(){

	Vector3 v1 = Vector3(size_p/2,size_p/2,size_p/2);
	Vector3 v2 = Vector3(-size_p/2,size_p/2,size_p/2);
	Vector3 v3 = Vector3(-size_p/2,-size_p/2,size_p/2);
	Vector3 v4 = Vector3(size_p/2,-size_p/2,size_p/2);
	Vector3 v5 = Vector3(-size_p/2,size_p/2,-size_p/2);
	Vector3 v6 = Vector3(-size_p/2,-size_p/2,-size_p/2);
	Vector3 v7 = Vector3(size_p/2,size_p/2,-size_p/2);
	Vector3 v8 = Vector3(size_p/2,-size_p/2,-size_p/2);

	Vector3 n,n1,n2,n3,n4;
	Vector3 vN1,vN2,vN3,vN4,vN5,vN6;

	glBegin(GL_QUADS);
	
	glColor3f(red,green,blue);
	
	//FRONT FACE 
	n1 = v3 - v2;
	n2 = v1 - v2;
	vN1 = n1.crossProduct(n2);
	vN1.normalise();
	glNormal3f(vN1.x,vN1.y,vN1.z);
	glVertex3f(v1.x,v1.y,v1.z);
	glVertex3f(v2.x,v2.y,v2.z);
	glVertex3f(v3.x,v3.y,v3.z);
	glVertex3f(v4.x,v4.y,v4.z);

	//LEFT FACE
	n1 = v6 - v5;
	n2 = v2 - v5;
	vN2 = n1.crossProduct(n2);
	n4 = vN2;
	vN2.normalise();
	glNormal3f(vN2.x,vN2.y,vN2.z);
	glVertex3f(v2.x,v2.y,v2.z);
	glVertex3f(v5.x,v5.y,v5.z);
	glVertex3f(v6.x,v6.y,v6.z);
	glVertex3f(v3.x,v3.y,v3.z);

	// BACK FACE
	n1 = v7 - v5;
	n2 = v6 - v5;
	vN3 = n1.crossProduct(n2);
	vN3.normalise();
	glNormal3f(vN3.x,vN3.y,vN3.z);
	glVertex3f(v7.x,v7.y,v7.z);
	glVertex3f(v5.x,v5.y,v5.z);
	glVertex3f(v6.x,v6.y,v6.z);
	glVertex3f(v8.x,v8.y,v8.z);

	// RIGHT FACE
	n1 = v4 - v1;
	n2 = v7 - v1;
	vN4 = n1.crossProduct(n2);
	vN4.normalise();
	glNormal3f(vN4.x,vN4.y,vN4.z);
	glVertex3f(v7.x,v7.y,v7.z);
	glVertex3f(v1.x,v1.y,v1.z);
	glVertex3f(v4.x,v4.y,v4.z);
	glVertex3f(v8.x,v8.y,v8.z);

	// TOP FACE
	n1 = v1 - v2;
	n2 = v5 - v2;
	vN5 = n1.crossProduct(n2);
	vN5.normalise();
	glNormal3f(vN5.x,vN5.y,vN5.z);
	glVertex3f(v1.x,v1.y,v1.z);
	glVertex3f(v2.x,v2.y,v2.z);
	glVertex3f(v5.x,v5.y,v5.z);
	glVertex3f(v7.x,v7.y,v7.z);

	// BOTTOM FACE
	n1 = v6 - v3;
	n2 = v4 - v3;
	vN6 = n1.crossProduct(n2);
	vN6.normalise();
	glNormal3f(vN6.x,vN6.y,vN6.z);
	glVertex3f(v4.x,v4.y,v4.z);
	glVertex3f(v3.x,v3.y,v3.z);
	glVertex3f(v6.x,v6.y,v6.z);
	glVertex3f(v8.x,v8.y,v8.z);
	
	glEnd();
	/*
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,1.0);
	glVertex3f(0.0f, 0.0f, size_p/2); // origin of the line
	glVertex3f(n3.x,n3.y,n3.z); // ending point of the line

	glColor3f(0.0,1.0,0.0);
	glVertex3f(size_p/2, 0.0f, 0.0f); // origin of the line
	glVertex3f(n4.x,n4.y,n4.z); // ending point of the line
	glEnd();
	/*
	glBegin(GL_LINES);

	glColor3f(1.0,0.0,0.0);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(0.0f, 100000.0f, 0.0f); // ending point of the line

	glColor3f(0.0,1.0,0.0);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(0.0f, 0.0f, 100000.0f); // ending point of the line

	glColor3f(0.0,0.0,1.0);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(100000.0f, 0.0f, 0.0f); // ending point of the line
	
	glEnd();*/

}
