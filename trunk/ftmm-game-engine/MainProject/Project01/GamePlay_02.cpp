#include "GamePlay_02.h"
#include "GameObject.h"
#include "Root.h"
//#include "SceneManager.h"
#define newCamera(x) SceneManager::getInstance()->createCamera(x)

GamePlay_02 * GamePlay_02::m_instance = NULL;

GamePlay_02 * GamePlay_02::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new GamePlay_02();
	}
	return m_instance;
}

GamePlay_02::GamePlay_02()
{
	name = "GamePlay_01";
	//newAgeCube = new CubeObjectTest("d", Vector3 (0.0,0.0,0.0), Quaternion.IDENTITY);
}

void GamePlay_02::init() 
{
	
	//SceneManager * sc_mn = SceneManager::getInstance();
	cam = newCamera("camera2");//SceneManager::getInstance()->createCamera("camera1");

	x_vel = 0;
	y_vel = 0;
	speed = 1;
	xrot = 1;
	yrot = 1;
	xrot_zero = 0;
	currentFramePositionx = 0;
	lastFramePositionx = 0;
	yrot_zero = 0;
	currentFramePositiony = 0;
	lastFramePositiony = 0;

	//newAgeCube = new CubeObjectTest("cube01", );

	Root * mRoot = Root::getInstance(); 

	cube_01 = new CubeObjectTest("node_44");
	
	cube_01->init(2);
	//cube_02->init(1);
	cam->setPosition(Vector3(0.0f,0.0f,-15.0f));
	//cube_02->mTransformNode->setPosition(Vector3(10.0,0.0,0.0));



}
//GamePlay_02::~GamePlay_02()
//{
//	SceneManager::getInstance()->destroyCamera("camera2");
//	delete cube_01;
//}
void GamePlay_02::destroy()
{
	SceneManager::getInstance()->destroyCamera("camera2");
	delete cube_01;
}

bool GamePlay_02::update(vector<Event*> events)
{
	Matrix3 * mt3 = new Matrix3;
	*mt3 = cam->getLocalAxes();
	
	for (vector<Event*>::iterator it = events.begin(); it != events.end(); ++it) 
	{
		if(CameraMovementInputEvent * cME = dynamic_cast<CameraMovementInputEvent *>(*it)) 
		{
			Vector2 position = cME->get_current_position();
			currentFramePositionx = position.x;
			currentFramePositiony = position.y;
		}
		if(FourDirectionsMovement_InputEvent * fDM = dynamic_cast<FourDirectionsMovement_InputEvent *>(*it)) 
		{
			x_vel = fDM->get_x_velocity();
			y_vel = fDM->get_y_velocity();
		}
	}


	if (x_vel != 0)
	{
		cam->translate((mt3->getColumn(0) * x_vel * speed),MovableObject::TransformSpace::TS_WORLD);
		
	}

	if (y_vel != 0)
	{
		cam->translate((mt3->getColumn(2) * y_vel * speed),MovableObject::TransformSpace::TS_WORLD);
	}

	cube_01->mTransformNode->rotate(Quaternion(9000,0.0,0.0,1.0), MovableObject::TransformSpace::TS_LOCAL);

	return true;
}

string GamePlay_02::get_name(){return name;}
