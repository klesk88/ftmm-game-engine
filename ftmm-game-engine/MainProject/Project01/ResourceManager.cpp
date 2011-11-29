#define NO_SDL_GLEXT
#include <GL\glew.h>

#include "ResourceManager.h"

ResourceManager * ResourceManager::p_instance = NULL;

ResourceManager * ResourceManager::getInstance()
{
	if(p_instance == NULL){
	
		p_instance = new ResourceManager();

	}

	return p_instance;
}

ResourceManager::ResourceManager()
{
	mesh_tab.clear();
}

Mesh* ResourceManager::loadMesh(const std::string& mesh_file)
{
	std::map<std::string, Mesh *>::iterator iter;
	iter = mesh_tab.find(mesh_file);
	Mesh* contenitor_mesh;
	std::list<Mesh *> mesh_list;

	if((iter) == mesh_tab.cend())
	{
		if (!Import3DFromFile(mesh_file))
		{	//error
			return false;
		}

		if(scene->HasMeshes())
		{
			contenitor_mesh = new Mesh(mesh_file);
			if(scene->mNumMeshes==1)
			{
				convertAIMeshToContenitorMesh(contenitor_mesh, scene->mMeshes[0]);
			}
			else
			{
				for(unsigned int n = 0; n < scene->mNumMeshes; ++n)
				{
					Mesh* sub_mesh = convertAIMeshToMesh(scene->mMeshes[n]);
					contenitor_mesh->addSubMesh(sub_mesh);
				}
			}
			mesh_tab.insert(std::pair<std::string,Mesh *>(mesh_file,contenitor_mesh));
			
			//OK
			return contenitor_mesh;
			
		}
		else
		{	//error
			return false;
		}
		
	}
	else
	{	//OK
		return iter->second;
	}

}

bool ResourceManager::Import3DFromFile(const std::string& pFile)
{
	//check if file exists
	std::ifstream fin(pFile.c_str());
	if(!fin.fail()) {
		fin.close();
	}
	else{
		printf("Couldn't open file: %s\n", pFile);
		printf("%s\n", importer.GetErrorString());
		return false;
	}

	scene = importer.ReadFile( pFile, aiProcessPreset_TargetRealtime_Quality |aiProcess_Triangulate | aiProcess_GenSmoothNormals);

	// If the import failed, report it
	if( !scene)
	{
		printf("%s\n", importer.GetErrorString());
		return false;
	}

	// Now we can access the file's contents.
	printf("Import of scene %s succeeded.",pFile.c_str());

	//importNameSubMesh(pFile);

	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}

Mesh* ResourceManager::convertAIMeshToMesh(aiMesh* ai_mesh)
{
	std::string temp_name;
	for(int i=0; i<ai_mesh->mName.length; i++)
		temp_name += ai_mesh->mName.data[i];

	Mesh* mesh_rtn = new Mesh(temp_name);

	mesh_rtn->m_num_vertices = ai_mesh->mNumVertices;
	mesh_rtn->m_vertices = new Vector3[mesh_rtn->m_num_vertices];
	mesh_rtn->m_normals = new Vector3[mesh_rtn->m_num_vertices];
	mesh_rtn->m_binormals = new Vector3[mesh_rtn->m_num_vertices];
	mesh_rtn->m_tangents = new Vector3[mesh_rtn->m_num_vertices];
	for (unsigned int i = 0 ; i < ai_mesh->mNumVertices ; i++) 
	{
		//Vector
        const aiVector3D* pPos      = &(ai_mesh->mVertices[i]);
		mesh_rtn->m_vertices[i].x = pPos->x;
		mesh_rtn->m_vertices[i].y = pPos->y;
		mesh_rtn->m_vertices[i].z = pPos->z;
		
		//Normal
		const aiVector3D* pNor      = &(ai_mesh->mNormals[i]);
		mesh_rtn->m_normals[i].x = pNor->x;
		mesh_rtn->m_normals[i].y = pNor->y;
		mesh_rtn->m_normals[i].z = pNor->z;

		//Bitangent - Binormal
		const aiVector3D* pBin      = &(ai_mesh->mBitangents[i]);
		mesh_rtn->m_binormals[i].x = pBin->x;
		mesh_rtn->m_binormals[i].y = pBin->y;
		mesh_rtn->m_binormals[i].z = pBin->z;

		//Tangent
		const aiVector3D* pTan      = &(ai_mesh->mTangents[i]);
		mesh_rtn->m_tangents[i].x = pTan->x;
		mesh_rtn->m_tangents[i].y = pTan->y;
		mesh_rtn->m_tangents[i].z = pTan->z;

	}

	//Index
	mesh_rtn->m_num_indices = ai_mesh->mNumFaces*3;
	mesh_rtn->m_num_faces = ai_mesh->mNumFaces;
	mesh_rtn->m_indices = new unsigned int[mesh_rtn->m_num_indices];
	int k=0;
	for (unsigned int i = 0 ; i < ai_mesh->mNumFaces ; i++) 
	{
		const aiFace& Face = ai_mesh->mFaces[i];
		mesh_rtn->m_indices[k] = Face.mIndices[0];
		mesh_rtn->m_indices[k+1] = Face.mIndices[1];
		mesh_rtn->m_indices[k+2] = Face.mIndices[2];
		k+=3;
	}

	mesh_rtn->initBuffer();

	return mesh_rtn;
}

void ResourceManager::convertAIMeshToContenitorMesh(Mesh* mesh, aiMesh* ai_mesh)
{
		//mesh->m_anim_meshes...
	//mesh->m_bitangents = new Vector3(ai_mesh->mBitangents->x,ai_mesh->mBitangents->y,ai_mesh->mBitangents->z);
	//mesh->m_bones....
	//mesh->m_colors...
	//mesh->face_array....
	//mesh->m_material_index;
	//mesh->m_num_anim_meshes;
	//mesh->m_num_bones;
//	mesh->m_num_faces;
	//mesh->m_num_uv_components;
//	mesh->m_num_vertices;
	//mesh->m_primitive_types;
	//mesh->m_tangents;

/*	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int i = 0 ; i < ai_mesh->mNumVertices ; i++) 
	{
        const aiVector3D* pPos      = &(ai_mesh->mVertices[i]);
        const aiVector3D* pNormal   = &(ai_mesh->mNormals[i]);
        const aiVector3D* pTexCoord = ai_mesh->HasTextureCoords(0) ? &(ai_mesh->mTextureCoords[0][i]) : &Zero3D;

		Vertex v(Vector3(pPos->x, pPos->y, pPos->z),
					 Vector2(pTexCoord->x, pTexCoord->y),
					 Vector3(pNormal->x, pNormal->y, pNormal->z));

		mesh->m_vertices.push_back(v);
    }

	for (unsigned int i = 0 ; i < ai_mesh->mNumFaces ; i++) 
	{
		const aiFace& Face = ai_mesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		mesh->m_indices.push_back(Face.mIndices[0]);
		mesh->m_indices.push_back(Face.mIndices[1]);
		mesh->m_indices.push_back(Face.mIndices[2]);
    }

	mesh->initBuffer();*/
}