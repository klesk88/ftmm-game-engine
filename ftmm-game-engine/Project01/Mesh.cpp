#include "Mesh.h"
#include "SceneManager.h"

Mesh::Mesh(float size, float r,float g,float b){

	size_p = size;
	red = r;
	green = g;
	blue = b;
}

void Mesh::drawCube(){

	Vector3 v1 = Vector3(size_p/2,size_p/2,size_p/2);
	Vector3 v2 = Vector3(-size_p/2,size_p/2,size_p/2);
	Vector3 v3 = Vector3(-size_p/2,-size_p/2,size_p/2);
	Vector3 v4 = Vector3(size_p/2,-size_p/2,size_p/2);
	Vector3 v5 = Vector3(-size_p/2,size_p/2,-size_p/2);
	Vector3 v6 = Vector3(-size_p/2,-size_p/2,-size_p/2);
	Vector3 v7 = Vector3(size_p/2,size_p/2,-size_p/2);
	Vector3 v8 = Vector3(size_p/2,-size_p/2,-size_p/2);

	Vector3 n,n1,n2,n3,n4;
	Vector3 vN1,vN2,vN3,vN4,vN5,vN6;

	glBegin(GL_QUADS);
	
	glColor3f(red,green,blue);
	
	/* FRONT FACE */
	n1 = v3 - v2;
	n2 = v1 - v2;
	vN1 = n1.crossProduct(n2);
	vN1.normalise();
	glNormal3f(vN1.x,vN1.y,vN1.z);
	glVertex3f(v1.x,v1.y,v1.z);
	glVertex3f(v2.x,v2.y,v2.z);
	glVertex3f(v3.x,v3.y,v3.z);
	glVertex3f(v4.x,v4.y,v4.z);

	/* LEFT FACE */
	n1 = v6 - v5;
	n2 = v2 - v5;
	vN2 = n1.crossProduct(n2);
	n4 = vN2;
	vN2.normalise();
	glNormal3f(vN2.x,vN2.y,vN2.z);
	glVertex3f(v2.x,v2.y,v2.z);
	glVertex3f(v5.x,v5.y,v5.z);
	glVertex3f(v6.x,v6.y,v6.z);
	glVertex3f(v3.x,v3.y,v3.z);

	/* BACK FACE */
	n1 = v7 - v5;
	n2 = v6 - v5;
	vN3 = n1.crossProduct(n2);
	vN3.normalise();
	glNormal3f(vN3.x,vN3.y,vN3.z);
	glVertex3f(v7.x,v7.y,v7.z);
	glVertex3f(v5.x,v5.y,v5.z);
	glVertex3f(v6.x,v6.y,v6.z);
	glVertex3f(v8.x,v8.y,v8.z);

	/* RIGHT FACE */
	n1 = v4 - v1;
	n2 = v7 - v1;
	vN4 = n1.crossProduct(n2);
	vN4.normalise();
	glNormal3f(vN4.x,vN4.y,vN4.z);
	glVertex3f(v7.x,v7.y,v7.z);
	glVertex3f(v1.x,v1.y,v1.z);
	glVertex3f(v4.x,v4.y,v4.z);
	glVertex3f(v8.x,v8.y,v8.z);

	/* TOP FACE */
	n1 = v1 - v2;
	n2 = v5 - v2;
	vN5 = n1.crossProduct(n2);
	vN5.normalise();
	glNormal3f(vN5.x,vN5.y,vN5.z);
	glVertex3f(v1.x,v1.y,v1.z);
	glVertex3f(v2.x,v2.y,v2.z);
	glVertex3f(v5.x,v5.y,v5.z);
	glVertex3f(v7.x,v7.y,v7.z);

	/* BOTTOM FACE */
	n1 = v6 - v3;
	n2 = v4 - v3;
	vN6 = n1.crossProduct(n2);
	vN6.normalise();
	glNormal3f(vN6.x,vN6.y,vN6.z);
	glVertex3f(v4.x,v4.y,v4.z);
	glVertex3f(v3.x,v3.y,v3.z);
	glVertex3f(v6.x,v6.y,v6.z);
	glVertex3f(v8.x,v8.y,v8.z);
	
	glEnd();
	/*
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,1.0);
	glVertex3f(0.0f, 0.0f, size_p/2); // origin of the line
	glVertex3f(n3.x,n3.y,n3.z); // ending point of the line

	glColor3f(0.0,1.0,0.0);
	glVertex3f(size_p/2, 0.0f, 0.0f); // origin of the line
	glVertex3f(n4.x,n4.y,n4.z); // ending point of the line
	glEnd();
	/*
	glBegin(GL_LINES);

	glColor3f(1.0,0.0,0.0);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(0.0f, 100000.0f, 0.0f); // ending point of the line

	glColor3f(0.0,1.0,0.0);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(0.0f, 0.0f, 100000.0f); // ending point of the line

	glColor3f(0.0,0.0,1.0);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(100000.0f, 0.0f, 0.0f); // ending point of the line
	
	glEnd();*/

}