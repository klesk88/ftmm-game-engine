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
#include "Vector3.h"


class Mesh
{
	protected:
		float size_p;
		float red, green, blue;

	public:

		#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX Mesh included")

		Mesh(float size,float red_,float green_,float blue_);
		void drawCube ();
};


#endif