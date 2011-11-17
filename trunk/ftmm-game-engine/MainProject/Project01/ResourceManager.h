#ifndef __ResourceManager_h__
#define __ResourceManager_H__

#include "Mesh.h"
// assimp include files. These three are usually needed.
#include <assimp.hpp>	
#include <aiPostProcess.h>
#include <aiScene.h>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <string>

class ResourceManager
{
	#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX Mesh included")
	public:
		//functions
			static ResourceManager * getInstance();
			Mesh* loadMesh(const std::string& mesh_file);
			void init();
		//variables
		
	private:
		//functions
			ResourceManager();
			bool Import3DFromFile(const std::string& pFile);
			Mesh* convertAIMeshToMesh(aiMesh* ai_mesh);
			void convertAIMeshToContenitorMesh(Mesh* mesh,aiMesh* ai_mesh);

		//variables
			static ResourceManager * p_instance;
			// Create an instance of the Importer class
			Assimp::Importer importer;
			// the global Assimp scene object
			const aiScene* scene;
			std::map<std::string, Mesh * > mesh_tab;

};

#endif