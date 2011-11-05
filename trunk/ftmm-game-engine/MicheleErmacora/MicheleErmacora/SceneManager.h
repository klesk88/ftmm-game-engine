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
#include "FrameListener.h"
#include "InputManager.h"
//----------------------
#include "TransformNode.h"
#include "RootTransformNode.h"
//#include "SceneManager.h"
#include <gl\gl.h>                         // Header File For The OpenGL32 Library
#include <gl\glu.h>                            // Header File For The GLu32 Library
#include <Windows.h>
#include <wchar.h>
#include "Vector4.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Vector2.h"
#include <typeinfo.h>

#include "GamePlay_01.h"






#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP     16

class SceneManager
{

	public:


		#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX SceneManager included")

		GamePlay_01 * gameState_01;

		static SceneManager * getInstance ();
		TransformNode * getRootTransformNode();
		Camera * createCamera(const std::string  & stringName);
		void renderScene();
		~SceneManager(){/*delete this;*/}
		//Texture function
		int LoadGLTextures(char*, int);
		GLuint getTexture(int);
		/*	@Param base_fps: how many fps you want
			@Param low_fps: minimum fps for having game logic at base fps speed
		*/
		void callGameLoop(bool,const int base_fps,const int low_fps);
		void createFrameListener(FrameListener*);
		/*
			i set the game_is:run variable so i know if the game loop have to start or not.
			after i call the method for call the game loop with the right parameters		
		*/
		void startEngine(bool,const int base_fps,const int low_fps);
		std::list <FrameListener*> framelistener_list;


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

		InputManager inputManager_instance;
		bool gameLoop(const int base_fps,const int low_fps);
		static SceneManager * p_instance;
		/*texture*/
		static const int size = 1;
		GLuint texture[size];


		//For FPS calculation
		Uint32 startclock;
		Uint32 deltaclock;
		Uint32 currentFPS;


		// ONLY FOR TESTING

		TransformNode * node1 ;
		TransformNode * node4 ;
		TransformNode * node2 ;
		TransformNode * node3 ;
		TransformNode * node5 ;
		SceneManager * sc_mng;
		float translate_ratio;
		GLfloat stam_arr[16];
		Mesh * cube ;
		Mesh * cube2;
		Camera * cam;
		Vector2 pos;
		int posx, posy;


};
#endif
