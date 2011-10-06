#include "SceneManager.h"

SceneManager::SceneManager(){

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

/* function to load in bitmap as a GL texture */
int SceneManager::LoadGLTextures(char* path, int position)
{
    /* Status indicator */
    int Status = FALSE;

    /* Create storage space for the texture */
    SDL_Surface *TextureImage[size]; 

    /* Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit */
    if ( ( TextureImage[0] = SDL_LoadBMP(path) ) )
        {

	    /* Set the status to true */
	    Status = TRUE;

	    /* Create The Texture */
	    glGenTextures( 1, &texture[position] );

	    /* Typical Texture Generation Using Data From The Bitmap */
	    glBindTexture( GL_TEXTURE_2D, texture[position] );

	    /* Generate The Texture */
	    glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[position]->w,
			  TextureImage[position]->h, 0, GL_BGR,
			  GL_UNSIGNED_BYTE, TextureImage[position]->pixels );

	    /* Linear Filtering */
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        }

    /* Free up any memory we may have used */
    if ( TextureImage[position] )
	    SDL_FreeSurface( TextureImage[position] );

	
    /* Enable Texture Mapping */
    glEnable( GL_TEXTURE_2D );

    return Status;
}

GLuint SceneManager::getTexture(int i)
{
	if((i>=0)&&(i<size))
		return texture[i];
	else
		return NULL;
}

Camera * SceneManager::createCamera(const std::string  & stringName){


	Camera * cam = new Camera (stringName);
	camera_list.push_back(cam);

	return cam;

}

void SceneManager::renderScene(){

	std::list<Camera*>::iterator cam_it;

	for ( cam_it = camera_list.begin(); cam_it != camera_list.end(); ++cam_it){
	
		(**cam_it).updateCamera();
		this->getRootTransformNode()->updateNode();

	}

}

void SceneManager::callGameLoop(const int base_fps,const int low_fps){
	gameLoop(base_fps,low_fps);
}

void SceneManager::createFrameListener(FrameListener* frame){

	framelistener_list.push_back(frame);
}

void SceneManager::startEngine(bool game_is_run,const int base_fps,const int low_fps){

	while(game_is_run)
	{
		gameLoop(base_fps,low_fps);
	}
}

void SceneManager::gameLoop(const int base_fps,const int low_fps){
		const int TICKS_PER_SECOND = base_fps;
		const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
		const int MAX_FRAMESKIP = low_fps;
	    DWORD next_game_tick = SDL_GetTicks();
		int loops;
		std::list<FrameListener*>::iterator i;
		
		

		   loops = 0;
		   while( unsigned int(SDL_GetTicks() - next_game_tick) > SKIP_TICKS && loops < MAX_FRAMESKIP) {
				
			   for(i=framelistener_list.begin(); i!=framelistener_list.end();i++){
				   if(  (*i)->frameStarted())
					  (*i)->notifyObjects();		
			   }
			   next_game_tick += SKIP_TICKS;
			   loops++;
			}
		renderScene();
		for(i=framelistener_list.begin(); i!=framelistener_list.end();i++){
			(*i)->frameEnded();		
		}
}
