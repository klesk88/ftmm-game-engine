#include "GamePlay_03.h"
#include "Root.h"
#define newCamera(x) SceneManager::getInstance()->createCamera(x)

GamePlay_03 * GamePlay_03::m_instance = NULL;

GamePlay_03 * GamePlay_03::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new GamePlay_03();
	}
	return m_instance;
}

GamePlay_03::GamePlay_03()
{
	name = "GamePlay_03";
	//newAgeCube = new CubeObjectTest("d", Vector3 (0.0,0.0,0.0), Quaternion.IDENTITY);
}

void GamePlay_03::init() 
{
	
	cam = newCamera("camera3");//SceneManager::getInstance()->createCamera("camera1");

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
	cam->setPosition(Vector3(0.0f,0.0f,-15.0f));

	Root * mRoot = Root::getInstance(); 

	playerCar = new PlayerCar("pCar_01");
	playerCar ->init();

	car = new CubeObjectTest("pCar_02");
	car ->init(1);

	car->mTransformNode->setPosition(Vector3(20.0,0.0,0.0));

}
//GamePlay_03::~GamePlay_03()
//{
//	SceneManager::getInstance()->destroyCamera("camera2");
//	delete playerCar;
//}

void GamePlay_03::destroy()
{
	SceneManager::getInstance()->destroyCamera("camera2");
	delete playerCar;
}

bool GamePlay_03::update(vector<Event*> events)
{
	//cout << "GP" << endl;
	Matrix3 * mt3 = new Matrix3;
	*mt3 = cam->getLocalAxes();
	
	for (vector<Event*>::iterator it = events.begin(); it != events.end(); ++it) 
	{
		//cout << "in gameplay update: for" << endl;
		//check whether its a CMIE
		if(CameraMovementInputEvent * cME = dynamic_cast<CameraMovementInputEvent *>(*it)) 
		{
			Vector2 position = cME->get_current_position();
			currentFramePositionx = position.x;
			currentFramePositiony = position.y;
			//cout << position.x << " . " << position.y << endl;
		}
		if(FourDirectionsMovement_InputEvent * fDM = dynamic_cast<FourDirectionsMovement_InputEvent *>(*it)) 
		{
			x_vel = fDM->get_x_velocity();
			y_vel = fDM->get_y_velocity();
		}

		//Here we demonstrate selecting events in the code for the level.
		//This is just an option in case the programmer wants to write some part of his
		//game logic inside the code for the game state instead of writing it inside
		//game objects.
		if(CarMovement_InputEvent * cM = dynamic_cast<CarMovement_InputEvent *>(*it))
		{
			playerCar->handleInput(cM);
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

	playerCar->update();

	/*
	xrot_zero = currentFramePositionx - lastFramePositionx;
	yrot_zero = currentFramePositiony - lastFramePositiony;
	lastFramePositionx = currentFramePositionx;
	lastFramePositiony = currentFramePositiony;
	xrot += xrot_zero;
	yrot += yrot_zero;
	cout << "xrot = "  ;
	cout << xrot << endl;
	if(xrot_zero != 0){
	
		xrot_zero /= xrot_zero;
		cam->rotate(Quaternion(100*xrot_zero,0.0,1.0,0.0), MovableObject::TransformSpace::TS_LOCAL);
	}
	if(yrot_zero != 0){
	
		yrot_zero /= yrot_zero;
	}
	//cam->setPosition(Vector3(0.0,0.0,-3.0));
	Quaternion q1;Quaternion q2;Quaternion final_rot;
	q1 = (Quaternion(xrot - 900 ,0.0,1.0,0.0));
	q2 = (Quaternion(yrot -  900,1.0,0.0,0.0));
	final_rot = q1 * q2;
	//cam->setOrientation(final_rot /*, MovableObject::TransformSpace::TS_LOCAL);
	//cam->rotate(Quaternion(100*xrot_zero,0.0,1.0,0.0), MovableObject::TransformSpace::TS_LOCAL);


	
	//cam->rotate(Quaternion(900,1.0,0.0,0.0),MovableObject::TS_PARENT);
	/*
	node3->setPosition(Vector3(1.2,0.0,0.0));
	node4->setPosition(Vector3(0.8,0.0,0.0));
	node2->rotate(Quaternion(9000,0.0,1.0,0.0),MovableObject::TS_PARENT);
	node3->rotate(Quaternion(8000,0.0,1.0,0.0),MovableObject::TS_PARENT);
	node5->setPosition(Vector3(1.2,0.0,0.0));
	node5->setOrientation(Quaternion(node4->getOrientation()));
	*/
	//cube_01->mTransformNode->rotate(Quaternion(9000,0.0,1.0,0.0),MovableObject::TS_PARENT);
	return true;
}

string GamePlay_03::get_name(){return name;}
