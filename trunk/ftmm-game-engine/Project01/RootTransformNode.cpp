#include "RootTransformNode.h"


RootTransformNode::RootTransformNode(const std::string & stringName,float x,float y,float z) : TransformNode(stringName,x,y,z){
}

RootTransformNode * RootTransformNode::p_instance = NULL;

RootTransformNode * RootTransformNode::getInstance(const std::string & stringName,float x,float y,float z){

	if(p_instance == NULL){
	
		p_instance = new RootTransformNode(stringName,x,y,z);

	}

	return p_instance;

}

