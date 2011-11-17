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

	//newAgeCube = new CubeObjectTest("cube01", );

	Root * mRoot = Root::getInstance(); 

	cube_01 = new CubeObjectTest("node_1");
	
	cube_02 = new CubeObjectTest("node_2");
	/*cube_03 = new CubeObjectTest("node_3");
	cube_04 = new CubeObjectTest("node_4");*/
	
	cube_01->init(1);
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

bool GamePlay_01::update()
{

	cam->setPosition(Vector3(0.0,0.0,-3.0));
	
	/*
	node3->setPosition(Vector3(1.2,0.0,0.0));
	node4->setPosition(Vector3(0.8,0.0,0.0));
	node2->rotate(Quaternion(9000,0.0,1.0,0.0),MovableObject::TS_PARENT);
	node3->rotate(Quaternion(8000,0.0,1.0,0.0),MovableObject::TS_PARENT);
	node5->setPosition(Vector3(1.2,0.0,0.0));
	node5->setOrientation(Quaternion(node4->getOrientation()));
	*/

	

	cube_01->mTransformNode->rotate(Quaternion(9000,0.0,1.0,0.0),MovableObject::TS_PARENT);

	return true;
}

string GamePlay_01::get_name(){return name;}
