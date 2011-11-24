#define NO_SDL_GLEXT
#include <GL\glew.h>
#include "Mesh.h"

#include <iostream>

using namespace std;

int Mesh::num_name = 0;

//New Version
Mesh::Mesh(std::string name)
{
	m_name = num_name;
	num_name +=1;
	vertex_buffer_obj = NULL;
	index_buffer = NULL;
	m_num_indices = 0;

	sub_mesh_tab.clear();

	// m_anim_meshes;
	//m_bitangents;
	//m_bones;
	//m_colors;
	//face_array;
	//m_material_index;
	//m_num_anim_meshes;
	//m_num_bones;
	//m_num_faces;
	//m_num_uv_components;
	//m_num_vertices = 0;
	//m_primitive_types;
	//m_tangents;
	m_vertices.clear();
	m_indices.clear();
}

Mesh::~Mesh()
{
	if(vertex_buffer_obj != NULL)
	{
		glDeleteBuffers(1, &vertex_buffer_obj);
	}
	if(index_buffer != NULL)
	{
		glDeleteBuffers(1, &index_buffer);
	}
}

void Mesh::addSubMesh(Mesh* sub_mesh)
{
	sub_mesh_tab.insert(std::pair<std::string, Mesh *>(sub_mesh->m_name, sub_mesh));
}

void Mesh::initBuffer()
{
	m_num_indices = m_indices.size();

	Vector3 * prova;
	prova = new Vector3[3];
	prova[0] = Vector3(-1.0,-1.0,0.0);
	prova[1] = Vector3(1.0,-1.0,0.0);
	prova[2] = Vector3(0.0,1.0,0.0);

	unsigned int * indices;
	indices = new unsigned int[3];
	indices[0] = 1;
	indices[1] = 2;
	indices[3] = 3;

	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
 
	glGenBuffers(1, &vertex_buffer_obj);
  	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * 3, &prova, GL_STATIC_DRAW);

    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3, &indices, GL_STATIC_DRAW);

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
	/*
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,0);
	glDisableClientState(GL_VERTEX_ARRAY);*/

	//Test Draw Line
	
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f,1.0f,0);
	for(int i=0; i<m_num_indices; i++)
	{
		int index = m_indices.at(i);
		glVertex3f(m_vertices[index].m_pos.x,m_vertices[index].m_pos.y,m_vertices[index].m_pos.z);
	}

	glEnd();
	//Old Version
	/*
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// bind VAO
	glBindVertexArray(vertex_buffer_obj);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

	glColor3f(1.0f,0,0);
	glEnableClientState(GL_VERTEX_ARRAY);

	int size = m_vertices.size()*3;
	m_array_vertices = new GLfloat[size];
	for(int i=0; i<m_vertices.size();)
	{
		m_array_vertices[i] = m_vertices[i%3].m_pos.x;
		m_array_vertices[i+1] = m_vertices[i%3].m_pos.y;
		m_array_vertices[i+2] = m_vertices[i%3].m_pos.z;

		i +=3;
	}
	glVertexPointer(3, GL_FLOAT, 0, &m_array_vertices);
	// draw
	glDrawArrays(GL_TRIANGLES,m_num_indices,GL_UNSIGNED_INT);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);*/

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
