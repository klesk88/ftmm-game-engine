/*
 * This is template created for Game Engines 2011 based on the SDL examples from http://nehe.gamedev.net/
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include "TransformNode.h"
#include <string>
#include "Mesh.h"
#include "RootTransformNode.h"
#include "SceneManager.h"


/* screen width, height, and bit depth */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP     16

/* Define our booleans */
#define TRUE  1
#define FALSE 0


TransformNode * node1 ;
//RootTransformNode * node4 ;
TransformNode * node2 ;
TransformNode * node3 ;
SceneManager * sc_mng;
float translate_ratio = 0.0;
//GLfloat arr[16];

bool rotateFlagUP = FALSE;
bool rotateFlagDOWN = FALSE;
bool rotateFlag = FALSE;
GLfloat angle = 0.05;



/* This is our SDL surface */
SDL_Surface *surface;

using namespace std;


/* function to release/destroy our resources and restoring the old desktop */
void Quit( int returnCode )
{
	/* clean up the window */
	SDL_Quit( );

	/* and exit appropriately */
	exit( returnCode );
}

/* function to reset our viewport after a window resize */
int resizeWindow( int width, int height )
{
	/* Height / width ration */
	GLfloat ratio;

	/* Protect against a divide by zero */
	if ( height == 0 )
	height = 1;

	ratio = ( GLfloat )width / ( GLfloat )height;

	/* Setup our viewport. */
	glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

	/* change to the projection matrix and set our viewing volume. */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	/* Set our perspective */
	gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

	/* Make sure we're chaning the model view and not the projection */
	glMatrixMode( GL_MODELVIEW );

	/* Reset The View */
	glLoadIdentity( );
	return( TRUE );
}


/* general OpenGL initialization function */
int initGL( GLvoid )
{

	/* Enable smooth shading */
	glShadeModel( GL_SMOOTH );

	/* Set the background Color*/
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	/* Depth buffer setup */
	glClearDepth( 17.0f );

	/* Enables Depth Testing */
	glEnable( GL_DEPTH_TEST );

	/* The Type Of Depth Test To Do */
	glDepthFunc( GL_LEQUAL );

	/* Really Nice Perspective Calculations */
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );


	//node1 = new RootTransformNode ("node1",0.0,0.0,0.0);
	sc_mng = SceneManager::getInstance();
	node1 = sc_mng->getRootTransformNode()->createChild("node1",0.0,0.0,0.0); 
	node2 = node1->createChild("node2",0.8,0.0,0.0);
	node3 = node2->createChild ("node3",0.5,0.0,0.0);
	//node4 = RootTransformNode::getInstance("root2",0.0,0.0,0.0);

	Mesh * cube = new Mesh(0.3,1.0,0.0,0.0);
	Mesh * cube2 = new Mesh(0.05,0.0,0.0,1.0);
	node2->attachObject(cube);
	node3->attachObject(cube2);
	
	
	/*
	std::list<std::string> * names = node1->getChildrenNames();
	std::list<std::string>::iterator i;
	for (i = names->begin(); i!=names->end(); ++i){
	
		std::cout << (*i) << std::endl;
	
	}
	*/

	return( TRUE );
}

void initScenegraph() 
{
	//create root node
	//add objects
}

/* function to handle key press events */
void handleKeyPress( SDL_keysym *keysym )
{
	switch ( keysym->sym )
	{
	case SDLK_ESCAPE:
		/* ESC key was pressed */
		Quit( 0 );
		break;
	case SDLK_F1:
		/* F1 key was pressed
		 * this toggles fullscreen mode
		 */
		SDL_WM_ToggleFullScreen( surface );
		break;
	case SDLK_DOWN:
		/* down  Rotation Mesh_02*/
		rotateFlagDOWN = TRUE;
		break;
	case SDLK_UP:
		/* up  Rotation Mesh_02*/
		rotateFlagUP = TRUE;
		break;
	case SDLK_RIGHT:
		/*start rotation*/
		rotateFlag=TRUE;
		break;
	case SDLK_LEFT:
		/*stop rotation*/
		rotateFlag=FALSE;
		break;
	default:
		break;
	}

	return;
}

/*
void rotation(Mesh * mesh, GLfloat angle, GLfloat valueX, GLfloat valueY, GLfloat valueZ)
{
	mesh->rotate_angle(angle);
	mesh->rotate_X(valueX);
	mesh->rotate_Y(valueY);
	mesh->rotate_Z(valueZ);
	mesh->draw();
	return;
}
*/
void pyramidizer(float offspring_x, float offspring_y, float offspring_z)

{
	glBegin(GL_TRIANGLES);

		glColor3f(1.0f,0.0f,0.0f);          // Red
		glVertex3f( 0.0f, 0.05f, 0.0f);          // Top Of Triangle (Front)
		glColor3f(0.0f,1.0f,0.0f);          // Green
		glVertex3f(-.05f,-.05f, 0.0f);          // Left Of Triangle (Front)
		glColor3f(0.0f,0.0f,1.0f);          // Blue
		glVertex3f( .05f,-.05f, 0.0f);          // Right Of Triangle (Front)

		/*
		glColor3f(1.0f,0.0f,0.0f);          // Red
		glVertex3f( offspring_x, offspring_y, offspring_z);          // Top Of Triangle (Right)
		glColor3f(0.0f,0.0f,1.0f);          // Blue
		glVertex3f( .05f,-.05f, .05f);          // Left Of Triangle (Right)
		glColor3f(0.0f,1.0f,0.0f);          // Green
		glVertex3f( .05f,-.05f, -.05f);         // Right Of Triangle (Right)

		glColor3f(1.0f,0.0f,0.0f);          // Red
		glVertex3f( offspring_x, offspring_y, offspring_z);          // Top Of Triangle (Back)
		glColor3f(0.0f,1.0f,0.0f);          // Green
		glVertex3f( .05f,-.05f, -.05f);         // Left Of Triangle (Back)
		glColor3f(0.0f,0.0f,1.0f);          // Blue
		glVertex3f(-.05f,-.05f, -.05f);         // Right Of Triangle (Back)

		glColor3f(1.0f,0.0f,0.0f);          // Red
		glVertex3f( offspring_x, offspring_y, offspring_z);          // Top Of Triangle (Left)
		glColor3f(0.0f,0.0f,1.0f);          // Blue
		glVertex3f(-.05f,-.05f,-.05f);          // Left Of Triangle (Left)
		glColor3f(0.0f,1.0f,0.0f);          // Green
		glVertex3f(-.05f,-.05f, .05f);          // Right Of Triangle (Left)
		*/
	glEnd();
}

void triangle_tester()
{
	GLfloat vertex_01[3] = {0.0f, 0.05f, 0.0f};
	GLfloat vertex_02[3] = {-0.05f, -0.05f, 0.05f};
	GLfloat vertex_03[3] = {0.05f, -0.05f, 0.05f};
	GLfloat color_01[3] = {1.0f, 0.0f, 0.0f};
	GLfloat color_02[3] = {1.0f, 0.0f, 0.0f};
	GLfloat color_03[3] = {1.0f, 0.0f, 0.0f};


	//mesh_01->create_triangle(vertex_01, vertex_02, vertex_03, color_01, color_02, color_03);
	//mesh_01->update();

	GLfloat vertex_011[3] = {0.0f, 0.25f, 0.0f};
	GLfloat vertex_021[3] = {-0.05f, 0.15f, 0.05f};
	GLfloat vertex_031[3] = {0.05f, 0.15f, 0.05f};
	GLfloat color_011[3] = {1.0f, 0.0f, 0.0f};
	GLfloat color_021[3] = {1.0f, 0.0f, 0.0f};
	GLfloat color_031[3] = {1.0f, 0.0f, 0.0f};

	//mesh_02->create_triangle(vertex_011, vertex_021, vertex_031, color_011, color_021, color_031);
	//mesh_02->update();
	//Do i need to manage display lists here??
}


/* Here goes our drawing code */
int drawGLScene( GLvoid )
{
	//GLfloat ratio;
	translate_ratio += 1;
	//GL_MODELVIEW_MATRIX = arr;
	//glLoadMatrixf(arr);
/*
	std::list<TransformNode*> * tn = node1->getChildrenPtr();

	if(tn->size()!= 0){

		std::list<TransformNode*>::iterator it3;
		for (it3 = tn->begin(); it3!= tn->end(); ++it3){
		
			std::cout << (**it3).getName()<< std::endl;
	
		}
	}
	else{
	
		std::cout << "non ha figli"<< std::endl;


	}
*/
	
	if ( translate_ratio == 5001){
		
		node3->changeParent(node1,0.0,0.0,0.0);
	}


	/* Clear The Screen And The Depth Buffer */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity();
	
	glTranslatef(0.0,0.0,-3.0);
	//gluLookAt(0.0,1.0,3.0,0.0,0.0,0.0,0.0,1.0,0.0);
	
	/*glPushMatrix();
	glTranslatef(translate_ratio/5,0.0,0.0);
	//glRotatef(translate_ratio * 10000,1.0,0.0,0.0);
	pyramidizer(5,5,5);
	glPopMatrix();*/

	
	glPushMatrix();
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

	glEnd();
	glPopMatrix();
	
	
	

	node1->updateNode();
	
	
	/*HERE you should put your code in order to do render something on the screen, use lighting, modify the camera position etc... */

	//TODO: why does it return 666 in the first run
	//GLfloat pass[3] = {mesh_01->get_translation(0)+movecam, mesh_01->get_translation(1), mesh_01->get_translation(2)};

	

	//	Testing basic vector operations
	//	Vector3 bla(3,4,5);
	//	cout << "3 =" << bla[0] << endl;

	
	
	/* Draw it to the screen */
	SDL_GL_SwapBuffers( );


	return( TRUE );
}



int main( int argc, char **argv )
{
	//triangle_tester();

	try{
	initScenegraph();

	/* Flags to pass to SDL_SetVideoMode */
	int videoFlags;
	/* main loop variable */
	int done = FALSE;
	/* used to collect events */
	SDL_Event event;
	/* this holds some info about our display */
	const SDL_VideoInfo *videoInfo;


	/* initialize SDL */
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		fprintf( stderr, "Video initialization failed: %s\n",
			 SDL_GetError( ) );
		Quit( 1 );
	}

	/* Fetch the video info */
	videoInfo = SDL_GetVideoInfo( );

	if ( !videoInfo )
	{
		fprintf( stderr, "Video query failed: %s\n",
			 SDL_GetError( ) );
		Quit( 1 );
	}

	/* the flags to pass to SDL_SetVideoMode */
	videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
	videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
	videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
	videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

	/* This checks to see if surfaces can be stored in memory */
	if ( videoInfo->hw_available )
	videoFlags |= SDL_HWSURFACE;
	else
	videoFlags |= SDL_SWSURFACE;

	/* This checks if hardware blits can be done */
	if ( videoInfo->blit_hw )
	videoFlags |= SDL_HWACCEL;

	/* Sets up OpenGL double buffering */
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	/* get a SDL surface */
	surface = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
				videoFlags );

	/* Verify there is a surface */
	if ( !surface )
	{
		fprintf( stderr,  "Video mode set failed: %s\n", SDL_GetError( ) );
		Quit( 1 );
	}

	/* initialize OpenGL */
	initGL( );

	/* resize the initial window */
	resizeWindow( SCREEN_WIDTH, SCREEN_HEIGHT );

	/* wait for events */ 
	while ( !done )
	{
		/* handle the events in the queue */

		while ( SDL_PollEvent( &event ) )
		{
			switch( event.type )
			{
			  
			case SDL_VIDEORESIZE:
				/* handle resize event */
				surface = SDL_SetVideoMode( event.resize.w,
							event.resize.h,
							16, videoFlags );
				if ( !surface )
				{
					fprintf( stderr, "Could not get a surface after resize: %s\n", SDL_GetError( ) );
					Quit( 1 );
				}
				resizeWindow( event.resize.w, event.resize.h );
				break;
			case SDL_KEYDOWN:
				/* handle key presses */
				handleKeyPress( &event.key.keysym );
				break;
			case SDL_QUIT:
				/* handle quit requests */
				done = TRUE;
				break;
			default:
				break;


			}
		}

		/* draw the scene */
		drawGLScene( );
	}

	if (done == true){
	
		delete sc_mng;
	
	}

	/* clean ourselves up and exit */
	Quit( 0 );

	/* Should never get here */
	return( 0 );
	}
	catch(char e){
		std::cout << "error  " << e << std::endl; 
	
	}
}