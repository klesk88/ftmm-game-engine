#include "Mesh.h"

Mesh::Mesh(float size, float r,float g,float b){

	size_p = size;
	red = r;
	green = g;
	blue = b;
}

void Mesh::drawCube(){

	glBegin(GL_QUADS);
	
	glColor3f(red,green,blue);
	glVertex3f(size_p/2,size_p/2,size_p/2);
	glVertex3f(-size_p/2,size_p/2,size_p/2);
	glVertex3f(-size_p/2,-size_p/2,size_p/2);
	glVertex3f(size_p/2,-size_p/2,size_p/2);


	glVertex3f(-size_p/2,size_p/2,size_p/2);
	glVertex3f(-size_p/2,size_p/2,-size_p/2);
	glVertex3f(-size_p/2,-size_p/2,-size_p/2);
	glVertex3f(-size_p/2,-size_p/2,size_p/2);


	glVertex3f(size_p/2,size_p/2,-size_p/2);
	glVertex3f(-size_p/2,size_p/2,-size_p/2);
	glVertex3f(-size_p/2,-size_p/2,-size_p/2);
	glVertex3f(size_p/2,-size_p/2,-size_p/2);


	glVertex3f(size_p/2,size_p/2,-size_p/2);
	glVertex3f(size_p/2,size_p/2,size_p/2);
	glVertex3f(size_p/2,-size_p/2,size_p/2);
	glVertex3f(size_p/2,-size_p/2,-size_p/2);


	glVertex3f(size_p/2,size_p/2,size_p/2);
	glVertex3f(-size_p/2,size_p/2,size_p/2);
	glVertex3f(-size_p/2,size_p/2,-size_p/2);
	glVertex3f(size_p/2,size_p/2,-size_p/2);


	glVertex3f(size_p/2,-size_p/2,size_p/2);
	glVertex3f(-size_p/2,-size_p/2,size_p/2);
	glVertex3f(-size_p/2,-size_p/2,-size_p/2);
	glVertex3f(size_p/2,-size_p/2,-size_p/2);
	
	
	glEnd();

}