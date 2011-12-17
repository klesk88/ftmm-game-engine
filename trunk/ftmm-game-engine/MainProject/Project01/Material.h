#ifndef  __MATERIAL_H__
#define  __MATERIAL_H__

//#include "Vector4.h"
//#include "Vector3.h"
#include "SDL.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "Light.h"
//#include "Root.h"
//#include "MovableObject.h"
//#include "TransformNode.h"


class Material
{

public:

	Material(const std::string name); 

	void setSpecularColour (float red, float green, float blue);

	void setDiffiuseColour (float red, float green, float blue);

	void setAmbientColour (float red, float green, float blue);

	void setShineValue (float val);

	std::string getName(void);

	void enableMaterial(void);

	void disableMaterial(void);


protected:

	std::string material_name;
	float m_diffuse[4];
	float m_specular[4];
	float m_ambient[4];
	float m_shine[1];
	GLuint m_program;
	



};


#endif