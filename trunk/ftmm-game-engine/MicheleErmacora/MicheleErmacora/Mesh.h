#ifndef __Mesh_H__
#define __Mesh_H__

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include <list>
#include <string>

class Mesh{


	public:
		Mesh(float size,float r,float g,float b);
		void drawCube ();

	protected:
		  float size_p;
		  float red, green, blue;

};


#endif