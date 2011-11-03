#include "SceneManager.h"


SceneManager::SceneManager(){

	//For FPS calculation
	startclock = 0;
	deltaclock = 0;
	currentFPS = 0;


	//FORT TESTING ONLY
	translate_ratio = 0.0;
	pos = Vector2(0.0,0.0);


	//game_is_run=false;//by default the game is run state is set to false so the game loop doesn't start until the user start it
	root_ptr = RootTransformNode::getInstance("Root");
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

	cam->setPosition(Vector3(0.0,0.0,-3.0));
	node3->setPosition(Vector3(1.2,0.0,0.0));
	node4->setPosition(Vector3(0.8,0.0,0.0));
	node2->rotate(Quaternion(9000,0.0,1.0,0.0),MovableObject::TS_PARENT);
	node3->rotate(Quaternion(8000,0.0,1.0,0.0),MovableObject::TS_PARENT);
	node5->setPosition(Vector3(1.2,0.0,0.0));
	node5->setOrientation(Quaternion(node4->getOrientation()));


	std::list<Camera*>::iterator cam_it;

	for ( cam_it = camera_list.begin(); cam_it != camera_list.end(); ++cam_it){
	
		(**cam_it).updateCamera();
		this->getRootTransformNode()->updateNode();

	}

	SDL_GL_SwapBuffers( );
}

void SceneManager::callGameLoop(bool game_is_run,const int base_fps,const int low_fps){
	
	// for FPS counting
	startclock = SDL_GetTicks();
	
	while(game_is_run)
	{
		game_is_run = gameLoop(base_fps,low_fps);

	}
}

void SceneManager::createFrameListener(FrameListener* frame){

	framelistener_list.push_back(frame);
}

void SceneManager::startEngine(bool game_is_run,const int base_fps,const int low_fps){

	callGameLoop(game_is_run,base_fps,low_fps);
}


bool SceneManager::gameLoop(const int base_fps,const int low_fps){
		const int TICKS_PER_SECOND = base_fps;
		const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
		const int MAX_FRAMESKIP = low_fps;
	    DWORD next_game_tick = SDL_GetTicks();
		int loops;
		bool game_is_run=true;
		std::list<FrameListener*>::iterator i;
		
		inputManager_instance.handle_input();
		
		//event_list.clear();

		// if input events have occured
		if(inputManager_instance.get_input_events().empty() == false)
		{
			// get input events
			vector<Event*> temp_vector = inputManager_instance.get_input_events();

			for (vector<Event*>::iterator it = temp_vector.begin(); it != temp_vector.end(); ++it) 
			{
				//check whether its a CMIE
				if(CameraMovementInputEvent * cME = dynamic_cast<CameraMovementInputEvent *>(*it)) 
				{
					Vector2 position = cME->get_current_position();
					cout << position.x << " . " << position.y << endl;
				}
			}
		}


		   loops = 0;
		   while( unsigned int(SDL_GetTicks() - next_game_tick) > SKIP_TICKS && loops < MAX_FRAMESKIP) {
				
			   for(i=framelistener_list.begin(); i!=framelistener_list.end();i++){
				   if(  (*i)->frameStarted())
					   game_is_run = (*i)->getEvents();		
			   }
			   next_game_tick += SKIP_TICKS;
			   loops++;
			}


		   renderScene();

		for(i=framelistener_list.begin(); i!=framelistener_list.end();i++){
			(*i)->frameEnded();		
		}


		// actual fps calculation inside loop
		deltaclock = SDL_GetTicks() - startclock;startclock = SDL_GetTicks();		
		if ( deltaclock != 0 )	currentFPS = 1000 / deltaclock;  
		cout<<"FPS: "<<currentFPS<<endl;

		return game_is_run;
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


		//sc_mng = SceneManager::getInstance();
		gameState_01 = GamePlay_01::getInstance();
		


		//node1 = new RootTransformNode ("node1",0.0,0.0,0.0);
	
		cam = createCamera("camera1");
		node1 = getRootTransformNode()->createChild("node1"); 
		node2 = node1->createChild("node2");
		node3 = node2->createChild ("node3",Vector3(0.2f,0.0f,0.0f));
		node4 = node3->createChild("node4");
		node5 = getRootTransformNode()->createChild("node5"); 
		//node1->getOrientation();

		cube = new Mesh(0.4,1.0,0.0,0.0);
		cube2 = new Mesh(0.3,0.0,0.0,1.0);
		Mesh * cube3 = new Mesh(0.2,0.0,1.0,0.0);
		Mesh * cube4 = new Mesh(0.3,0.5,0.0,0.5);

		node2->attachObject(cube);
		node3->attachObject(cube2);
		node4->attachObject(cube3);
		node5->attachObject(cube4);
		node2->setOrientation(Quaternion(12,0.0,0.0,1.0));


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
