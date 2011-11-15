#ifndef __GamePlay_01_H__
#define __GamePlay_01_H__

#include "GameState.h"
#include "GameObject.h"
#include "CubeObjectTest.h"
#include <string>
#include "SceneManager.h"
using namespace std;

#pragma once

// You could also call this our first level
class GamePlay_01 : public GameState
{
private:


		// ONLY FOR TESTING
		TransformNode * node1 ;
		TransformNode * node4 ;
		TransformNode * node2 ;
		TransformNode * node3 ;
		TransformNode * node5 ;
		float translate_ratio;
		GLfloat stam_arr[16];
		Mesh * cube ;
		Mesh * cube2;
		Camera * cam;
		Vector2 pos;
		int posx, posy;
		//end
		
		CubeObjectTest newAgeCube;
		static GamePlay_01 * m_instance;
		~GamePlay_01();

		string name;

	protected:
		GamePlay_01();
public:

		
		CubeObjectTest * cube_01;
		CubeObjectTest * cube_02;
		CubeObjectTest * cube_03;
		CubeObjectTest * cube_04;

		#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX GamePlay_01 included")
		
		string get_name();
		
		static GamePlay_01 * getInstance ();
		void init();
		
		void loadStuff();

		bool update();
};
#endif
