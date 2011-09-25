#include "TransformNode.h"
#include "SceneManager.h"

TransformNode::TransformNode(const std::string & stringName, float x,float y,float z){

	node_name = stringName;
	relative_x = x;
	relative_y = y;
	relative_z = z;

}

TransformNode * TransformNode::createChild(const std::string & stringName, float x,float y,float z){

	SceneManager * sc_mn = SceneManager::getInstance();
	sc_mn->getRootTransformNode()->matchNames(stringName);
	TransformNode * temp_node = new TransformNode(stringName, x,y,z);
	temp_node->setParent(this);
	child_list.push_back(temp_node);
	children_names.push_back(stringName);

	return temp_node;
	
}

std::string TransformNode::getName(){

	return node_name;
}

std::list<std::string> * TransformNode::getChildrenNames(){

	
	return & children_names;
}

void TransformNode::attachObject(Mesh * mesh_ptr){

	//mesh_attached = mesh_ptr;
	Mesh * mesh_attached = mesh_ptr;
	attached_obj.push_back(mesh_attached);

}

void TransformNode::updateNode(){

	translate_ratio += 0.003; 
	glPushMatrix();
	
	glTranslatef(relative_x,relative_y,relative_z);
	glRotatef(translate_ratio * 5,0.0,1.0,0.0);
	if(attached_obj.size() != 0) { 
		
		std::list<Mesh*>::iterator it;
		for (it = attached_obj.begin(); it!= attached_obj.end(); ++it){
	
			(**it).drawCube();
			//glTranslatef(0.3,0.0,0.0);
			//glColor3f(1.0f,0.0f,0.0f);
	
		}
	}

	
	if (child_list.size() != 0){

		
		std::list<TransformNode*>::iterator it2;
		for(it2 = child_list.begin(); it2 != child_list.end(); ++it2){
	
			(**it2).updateNode();
	
		}
		
	}
	
	glPopMatrix();

}

std::list<Mesh*> * TransformNode::getAttachedObjectPtr(){

	return &attached_obj;

}

void TransformNode::setParent(TransformNode * parent){

	parent_ptr = parent;

}

TransformNode * TransformNode::getParent(){

	if (parent_ptr != NULL){
	
		return parent_ptr;
	}

	else {
	
		return this;
	
	}

}

void TransformNode::deleteChild(TransformNode * child_ptr){

	child_list.remove(child_ptr);


}

std::list<TransformNode*> * TransformNode::getChildrenPtr(){

	return &child_list;


}

void TransformNode::changeParent(TransformNode * new_parent,float x,float y,float z){

	TransformNode * temp_parent_ptr = this->getParent();
	new_parent->insertChildInList(this);
	temp_parent_ptr->deleteChild(this);
	relative_x = x;
	relative_y = y;
	relative_z = z;


}

void TransformNode::insertChildInList(TransformNode * new_child){

	child_list.push_back(new_child);

}

void TransformNode::matchNames(std::string matching_name){

	if (node_name == matching_name){
	
		throw "it works";
	}

	else if (child_list.size() != 0){
	
		std::list<TransformNode*>::iterator it;
		for (it = child_list.begin(); it!= child_list.end(); ++it){
			
			(*it)->matchNames(matching_name);
		
		}
	
	}

}