#include "GamePlay_01.h"
#include "Root.h"
//#include "SceneManager.h"
#define newCamera(x) SceneManager::getInstance()->createCamera(x)

GamePlay_01 * GamePlay_01::m_instance = NULL;

GamePlay_01 * GamePlay_01::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new GamePlay_01();
	}
	return m_instance;
}

GamePlay_01::GamePlay_01()
{
	name = "GamePlay_01";
	//newAgeCube = new CubeObjectTest("d", Vector3 (0.0,0.0,0.0), Quaternion.IDENTITY);
}

void GamePlay_01::init() 
{
	
	//SceneManager * sc_mn = SceneManager::getInstance();
	cam = newCamera("camera1");//SceneManager::getInstance()->createCamera("camera1");

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

	cube_01 = new CubeObjectTest("node_1");
	//cube_02 = new CubeObjectTest("node_2");
	/*cube_03 = new CubeObjectTest("node_3");
	cube_04 = new CubeObjectTest("node_4");*/
	
	cube_01->init(1);
	//cube_02->init(3);
	cam->setPosition(Vector3(0.0f,0.0f,-15.0f));
	//cube_02->mTransformNode->setPosition(Vector3(10.0,0.0,0.0));

	//cube_02->init(2);
	/*
	cube_02->init();
	cube_02->init();
	cube_02->init();*/

	/*
	node1 = mRoot->mRootTransformNode->createChild("node1"); 
	node2 = node1->createChild("node2");
	node3 = node2->createChild ("node3",Vector3(0.2f,0.0f,0.0f));
	node4 = node3->createChild("node4");
	node5 = mRoot->mRootTransformNode->createChild("node5"); 
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
	*/
}

void GamePlay_01::destroy()
{
	SceneManager::getInstance()->destroyCamera("camera1");
	cube_01->destroy();
} 

bool GamePlay_01::update(vector<Event*> events)
{
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
	//cube_01->mTransformNode->scale(Vector3(0.001,0.001,0.001));
	//cube_01->mTransformNode->translate(Vector3(0.001,0.001,0.001),MovableObject::TransformSpace::TS_LOCAL);

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

string GamePlay_01::get_name(){return name;}
