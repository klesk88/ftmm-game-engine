#ifndef __TransformNode_H__
#define __TransformNode_H__

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include <list>
#include <string>
#include "Mesh.h"


class TransformNode{

	public:

		
	
		//Method to create a child of a TransformNode.
		TransformNode * createChild(const std::string & stringName, float x,float y,float z);
		
		//Method to get the name of this TransformNode
		std::string getName();
		std::list<std::string> * getChildrenNames();
		
		//A TranformNode can have an object attached like a mesh.
		void attachObject(Mesh * mesh_ptr);
		
		//This method updates all its transformations and the transformations of all the children
		void updateNode ();
		
		//This method provides a pointer of a list of pointers of all object attached to the node
		std::list<Mesh*> * getAttachedObjectPtr();
		
		/*This method returns a pointer to the parent of the TransformNode. Noticed that the parent of the
		Root is the same Root*/
		TransformNode * getParent();
		
		//This metod allows to change the parent in runtime attaching the TranformNode to another parent
		void changeParent(TransformNode * new_parent,float x,float y,float z);
		
		//This method returns a pointer of a list of pointers of all the children of the TranformNode
		std::list<TransformNode*> * getChildrenPtr();
		
		~TransformNode(){delete this;}

	protected:

		/*Constructor. TransformNodes’s constructor needs a string that 
		identify the node’s name and a Vector3 and Quaternion to specify 
		the position and the orientation of the node according to his parent. 
		Notice that if you want to create a TransformNode you need to call 
		the method createChild, since all TranformNodes are children of a 
		Root that is automatically created by the SceneManager. If you want 
		to create a node that is child of the Root you have to call the method 
		getRootTranformNode from the SceneManager.*/
		TransformNode(const std::string & stringName,float x,float y,float z);

		std::list<TransformNode*> child_list;
		std::string node_name;
		std::list<std::string> children_names;
		//Mesh * mesh_attached;
		std::list<Mesh*> attached_obj;
		float relative_x;
		float relative_y;
		float relative_z;
		float translate_ratio;
		void matchNames ( std::string matching_name);
		void setParent(TransformNode * parent);
		TransformNode * parent_ptr;
		void deleteChild (TransformNode * child_ptr);
		void insertChildInList(TransformNode * new_child);





};

#endif