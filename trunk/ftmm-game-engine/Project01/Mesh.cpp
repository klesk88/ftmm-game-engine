#include "Mesh.h"
#include "SceneManager.h"

Mesh::Mesh(float size, float r,float g,float b){

	size_p = size;
	red = r;
	green = g;
	blue = b;
}

void Mesh::drawCube(){


	/* Select Our Texture */
	glBindTexture( GL_TEXTURE_2D, SceneManager::getInstance()->getTexture(0) );


	glBegin(GL_QUADS);
	
	glColor3f(1.0,1.0,1.0);
	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f(size_p/2,size_p/2,size_p/2);
	
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f(-size_p/2,size_p/2,size_p/2);
	
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f(-size_p/2,-size_p/2,size_p/2);
	glTexCoord2f( 0.0f, 1.0f );
	
	glVertex3f(size_p/2,-size_p/2,size_p/2);


	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f(-size_p/2,size_p/2,size_p/2);
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f(-size_p/2,size_p/2,-size_p/2);
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f(-size_p/2,-size_p/2,-size_p/2);
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f(-size_p/2,-size_p/2,size_p/2);

	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f(size_p/2,size_p/2,-size_p/2);
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f(-size_p/2,size_p/2,-size_p/2);
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f(-size_p/2,-size_p/2,-size_p/2);
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f(size_p/2,-size_p/2,-size_p/2);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(1.0,1.0,1.0);
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