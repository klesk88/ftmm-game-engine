#define NO_SDL_GLEXT
#include <GL\glew.h>
#include "Material.h"
#include "MaterialManager.h"
#include "SceneManager.h"

Material::Material(const std::string name){

	
	m_diffuse[0] = 1.0;
	m_diffuse[1] = 0.0;
	m_diffuse[2] = 0.0;
	m_diffuse[3] = 1.0;
	m_specular[0] = 0.8;
	m_specular[1] = 0.8;
	m_specular[2] = 0.8;
	m_specular[3] = 1.0;
	m_ambient[0] = 0.3;
	m_ambient[1] = 0.3;
	m_ambient[2] = 0.3;
	m_ambient[3] = 1.0;
	m_shine[0] = 110.0;
	m_program = MaterialManager::getInstance()->getDefaultMaterialProgram();

}

std::string Material::getName(){

	return material_name;

}

void Material::setAmbientColour(float red, float green, float blue){

	m_ambient[0] = red;
	m_ambient[1] = green;
	m_ambient[2] = blue;

}

void Material::setDiffiuseColour(float red, float green, float blue){

	m_diffuse[0] = red;
	m_diffuse[1] = green;
	m_diffuse[2] = blue;

}

void Material::setShineValue(float val){

	m_shine[0] = val;

}

void Material::setSpecularColour(float red, float green, float blue){

	m_specular[0] = red;
	m_specular[1] = green;
	m_specular[2] = blue;

}

void Material::enableMaterial(){

	glUseProgram(m_program);

	GLint val = glGetUniformLocation(m_program, "diffuseVal");
	glUniform4f(val,m_diffuse[0],m_diffuse[1],m_diffuse[2],m_diffuse[3]);

	GLint val2 = glGetUniformLocation(m_program, "specularVal");
	glUniform4f(val2,m_specular[0],m_specular[1],m_specular[2],m_specular[3]);

	GLint val3 = glGetUniformLocation(m_program, "ambientVal");
	glUniform4f(val3,m_ambient[0],m_ambient[1],m_ambient[2],m_ambient[3]);

	/*GLint val4 = glGetUniformLocation(m_program, "shine");
	glUniform1f(val4,m_shine[0]);*/

	

	//SceneManager::getInstance()->getSceneLights(lt);
	//int i = lt[0].getType();

}

void Material::disableMaterial(){

	glUseProgram(0);

}