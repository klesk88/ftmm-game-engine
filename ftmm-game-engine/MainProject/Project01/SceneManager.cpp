#include "SceneManager.h"
#include "Root.h"


SceneManager::SceneManager()
{
	//Root *mRoot = Systems::getInstance();
	//std::cout << "listen: " << mRoot->get_current_GameState()->name() << std::endl;
	//mRoot->gamePlay_01->loadStuff();

	//FORT TESTING ONLY
	translate_ratio = 0.0;
	pos = Vector2(0.0,0.0);

	//game_is_run=false;//by default the game is run state is set to false so the game loop doesn't start until the user start it
	//root_ptr = RootTransformNode::getInstance("Root");
	root_ptr = Root::getInstance()->mRootTransformNode;
}



SceneManager * SceneManager::p_instance = NULL;

SceneManager * SceneManager::getInstance(){

	if(p_instance == NULL){
	
		p_instance = new SceneManager();

	}

	return p_instance;

}

TransformNode * SceneManager::getRootTransformNode(){

	return root_ptr;
}

Camera * SceneManager::createCamera(const std::string  & stringName){


	Camera * cam = new Camera (stringName);
	camera_list.push_back(cam);

	return cam;

}

void SceneManager::renderScene(){

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	std::list<Camera*>::iterator cam_it;

	for ( cam_it = camera_list.begin(); cam_it != camera_list.end(); ++cam_it){
	
		(**cam_it).updateCamera();
		this->getRootTransformNode()->updateNode();

	}

	SDL_GL_SwapBuffers( );
}


int SceneManager::initializeEngine()
{

	try
	{
		
		SDL_Surface *surface;
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
		/* Enable smooth shading */
		glShadeModel( GL_SMOOTH );

		/* Set the background Color*/
		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

		/* Depth buffer setup */
		glClearDepth( 17.0f );

		/* Enables Depth Testing */
		glEnable( GL_DEPTH_TEST );

		/* Enables Light */
		//glEnable( GL_LIGHTING);
		

		/*Enable gouraud shading */
		glShadeModel(GL_SMOOTH);	

		/* The Type Of Depth Test To Do */
		glDepthFunc( GL_LEQUAL );

		/* Really Nice Perspective Calculations */
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

		GLfloat ratio;

		/* Protect against a divide by zero */
		

		ratio = SCREEN_WIDTH/SCREEN_HEIGHT;
		/* Setup our viewport. */
		glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );

		/* change to the projection matrix and set our viewing volume. */
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity( );

		/* Set our perspective */
		gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

		/* Make sure we're chaning the model view and not the projection */
		glMatrixMode( GL_MODELVIEW );

		/* Reset The View */
		glLoadIdentity( );

		/* Should never get here */
		return( 0 );
	}
		catch(char e)
		{		
			std::cout << "error  " << e << std::endl; 
		}

}

//deleteEngine

		/* clean ourselves up and exit */
		//Quit( 0 );
