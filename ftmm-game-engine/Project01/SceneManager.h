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


class SceneManager
{

	public:
		
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
	protected:

		SceneManager();
		TransformNode * root_ptr;
		std::list <Camera*> camera_list;
		

	private:

		bool gameLoop(const int base_fps,const int low_fps);
		static SceneManager * p_instance;
		/*texture*/
		static const int size = 1;
		GLuint texture[size];


};
#endif
