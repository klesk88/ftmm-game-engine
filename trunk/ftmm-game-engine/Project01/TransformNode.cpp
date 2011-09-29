#include "TransformNode.h"
#include "SceneManager.h"

TransformNode::TransformNode(const std::string & stringName, Vector3 initial_position ){

	node_name = stringName;
	

	arr[0] = 1 ;
	arr[1] =0 ;
	arr[2] = 0;
	arr[3] = 0;
	arr[4] = 0;
	arr[5] = 1;
	arr[6] = 0;
	arr[7] = 0;
	arr[8] =0 ;
	arr[9] = 0;
	arr[10] = 1;
	arr[11] = 0;
	arr[12] = 0;
	arr[13] = 0;
	arr[14] =0 ;
	arr[15] =1 ;

}

TransformNode * TransformNode::createChild(const std::string & stringName, Vector3 initial_position ){

	SceneManager * sc_mn = SceneManager::getInstance();
	sc_mn->getRootTransformNode()->matchNames(stringName);
	TransformNode * temp_node = new TransformNode(stringName, initial_position);
	temp_node->setParent(this);
	child_list.push_back(temp_node);
	

	
	return temp_node;
	
}

std::string TransformNode::getName(){

	return node_name;
}



void TransformNode::attachObject(Mesh * mesh_ptr){

	//mesh_attached = mesh_ptr;
	Mesh * mesh_attached = mesh_ptr;
	attached_obj.push_back(mesh_attached);

}

void TransformNode::updateNode(){

	translate_ratio = 0.3;
	
	glPushMatrix();
	glMultMatrixf(arr);
	glGetFloatv(GL_MODELVIEW_MATRIX,arr2);

	//glTranslatef(relative_x,relative_y,relative_z);
	//glRotatef(translate_ratio * 5,0.0,1.0,0.0);
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

void TransformNode::changeParent(TransformNode * new_parent,Vector3 initial_position ){

	TransformNode * temp_parent_ptr = this->getParent();
	new_parent->insertChildInList(this);
	temp_parent_ptr->deleteChild(this);
	

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

void TransformNode::stampMatrix(){

	for (int i=0;i<4;i++){

		std::cout << arr2[i];
		std::cout << ",";
		std::cout << arr2[i+4];
		std::cout << ",";
		std::cout << arr2[i+8];
		std::cout << ",";
		std::cout << arr2[i+12];
		std::cout << "  " << std::endl;
		
	}
	std::cout<<"     " <<std::endl;

}


const Quaternion& MovableObject::getOrientation() const{

	return global_transform.extractQuaternion();
}

const Vector3 & MovableObject::getScale() const{

	return global_transform.getScale();

}

const Vector3 & MovableObject::getPosition() const{

	//global_transform
	
	return global_transform.getTrans();
}

void MovableObject::translate (const Vector3& translation_value, TransformSpace relativeTo){
	
	/*global_transform[0][3] 
	global_transform[1][3]
	global_transform[2][3]*/
}

void MovableObject::setPosition(const Vector3& position_value){

	global_transform[0][3] = position_value.x;
	global_transform[1][3] = position_value.y;
	global_transform[2][3] = position_value.z;

}

void MovableObject::rotate(const Vector3& axis, const Radian& angle, TransformSpace relativeTo){
}

void MovableObject::rotate(const Quaternion& rotation_value, TransformSpace relativeTo){
}

void MovableObject::roll(const Radian& angle, TransformSpace relativeTo ){
}

void MovableObject::pitch(const Radian& angle, TransformSpace relativeTo ){
}

void MovableObject::yaw(const Radian& angle, TransformSpace relativeTo ){
}

void MovableObject::setOrientation(const Quaternion & orientation_value){
}

void MovableObject::scale(const Vector3& scale_value){

	Vector3 sc = global_transform.getScale() + scale_value;
	global_transform.setScale(sc);

}

void MovableObject::setScale(const Vector3& scale_value){

	global_transform.setScale(scale_value);
}