#ifndef __SceneManager_H__
#define __SceneManager_H__

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include <list>
#include <string>
#include "Mesh.h"
#include "RootTransformNode.h"
#include "Camera.h"

class SceneManager{

	public:

		static SceneManager * getInstance ();
		TransformNode * getRootTransformNode();
		Camera * createCamera(const std::string  & stringName);
		void renderScene();
		~SceneManager(){delete this;}
		//Texture function
		int LoadGLTextures(char*, int);
		GLuint getTexture(int);

	protected:
		SceneManager();
		TransformNode * root_ptr;
		std::list <Camera*> camera_list;

	private:

		static SceneManager * p_instance;
		/*texture*/
		static const int size = 1;
		GLuint texture[size];


};


#endif