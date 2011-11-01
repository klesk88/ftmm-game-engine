
#include "GamePlay_01.h"

GamePlay_01 * GamePlay_01::p_instance = NULL;

GamePlay_01::GamePlay_01(){}


GamePlay_01 * GamePlay_01::getInstance()
{
	if(p_instance == NULL)
	{
		p_instance = new GamePlay_01();
	}
	return p_instance;
}

void GamePlay_01::init() 
{
	/*
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
	*/
}
