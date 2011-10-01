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

class SceneManager{

	public:

		static SceneManager * getInstance ();
		TransformNode * getRootTransformNode();
		~SceneManager(){delete this;}
		//Texture function
		int LoadGLTextures(char*, int);
		GLuint getTexture(int);

	protected:
		SceneManager();
		TransformNode * root_ptr;

	private:

		static SceneManager * p_instance;
		/*texture*/
		static const int size = 1;
		GLuint texture[size];


};


#endif