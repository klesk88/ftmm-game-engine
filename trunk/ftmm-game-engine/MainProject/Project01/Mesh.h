#ifndef __Mesh_H__
#define __Mesh_H__

#pragma once
#include "SDL.h"
#include "SDL_opengl.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"
#include <string>
#include <map>
#include <vector>

struct Vertex
{
	Vector3 m_pos;
	Vector2 m_tex;
	Vector3 m_normal;

	Vertex(const Vector3 pos, const Vector2 tex, const Vector3 normal)
	{
		m_pos = pos;
		m_tex = tex;
		m_normal = normal;
	}
};


class Mesh
{
	friend class ResourceManager;

	//New version
	public:
		void renderMesh();
		bool hasSubMesh();
		std::map<std::string, Mesh *> sub_mesh_tab;

	private:
		Mesh(std::string name);
		~Mesh();
		void addSubMesh(Mesh* sub_mesh);
		void initBuffer();

		//Only Contenitor variables

		//SubMesh variables
		GLuint vertex_buffer_obj;
		GLuint index_buffer;
		GLuint VAO;
        unsigned int m_num_indices;

		//aiAnimMesh ** m_anim_meshes;
		//Vector3 * m_bitangents;
		//aiBone ** m_bones;
		//Vector4 * m_colors;
		//unsigned int * face_array;
		//unsigned int m_material_index;
		std::string m_name;
		//unsigned int m_num_anim_meshes;
		//unsigned int m_num_bones;
		//unsigned int m_num_faces;
		//unsigned int m_num_uv_components;
		//unsigned int m_num_vertices;
		//unsigned int m_primitive_types;
		//Vector3 * m_tangents;
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		GLfloat* m_array_vertices;

		static int num_name;




	//old Version
		
	protected:
		float size_p;
		float red, green, blue;

	public:

		#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX Mesh included")

		Mesh(float size,float red_,float green_,float blue_)
		{
			size_p = size;
			red = red_;
			green = green_;
			blue = blue_;
		}
		void drawCube ();
		
};


#endif