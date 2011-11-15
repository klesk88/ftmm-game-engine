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
//#include "RootTransformNode.h"
class RootTransformNode;
#include "Camera.h"
//#include "FrameListener.h"
//----------------------
#include "TransformNode.h"
#include "RootTransformNode.h"
//#include "SceneManager.h"
#include <gl\gl.h>                         // Header File For The OpenGL32 Library
#include <gl\glu.h>                            // Header File For The GLu32 Library
#include <Windows.h>
#include <wchar.h>
//#include "Vector4.h"
//#include "Vector3.h"
//#include "Matrix4.h"
#include "Vector2.h"
//#include <typeinfo.h>

//#include "GamePlay_01.h"
class Root;

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP     16

class SceneManager
{

	public:

		//Root * m_Root;

		#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX SceneManager included")

		static SceneManager * getInstance ();
		TransformNode * getRootTransformNode();
		Camera * createCamera(const std::string  & stringName);
		void renderScene();
		~SceneManager();//{/*delete this;*/}

		//Texture function
		int LoadGLTextures(char*, int);
		GLuint getTexture(int);
	
		//FT
		/*Provisory init for the whole engine*/
		int initializeEngine();
		void Quit( int returnCode )
		{
			/* clean up the window */
			SDL_Quit( );

			/* and exit appropriately */
			exit( returnCode );
		}

	protected:

		SceneManager();
		TransformNode * root_ptr;
		std::list <Camera*> camera_list;

	private:

		static SceneManager * p_instance;
		/*texture*/
		static const int size = 1;
		GLuint texture[size];

		// ONLY FOR TESTING
		float translate_ratio;
		Vector2 pos;
};
#endif
