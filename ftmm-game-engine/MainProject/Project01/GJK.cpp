#include "GJK.h"
#include "Matrix4.h"

GJK::GJK(Collidable* collider1, Collidable* collider2){

	//initialize the distance vector
	d= new Vector3[1];
	d[0].x =1;
	d[0].y =1;
	d[0].z=1;

	//initialize simplex
	simplex = new Vector3[3];
	simplex[0].x =0;
	simplex[0].y =0;
	simplex[0].z=0;

	object1 = collider1;
	object2 = collider2;
}
	



void GJK::minkowskiDifference(){

	shape = new Vector3[8];
	for(int i=0; i<(object1->m_bounding_box)->length(); i++){
		shape[i].x= object1->m_bounding_box->x - object2->m_bounding_box->x;
	}
	
}

void GJK::updateSimplex(){
	//temp variables
	//for first object
	Vector3 temp_min;
	temp_min.x=0;
	temp_min.y=0;
	temp_min.z=0;

	Vector3 d1;
	d1.x=0;
	d1.y=0;
	d1.z=0;
	//for second object
	Vector3 temp_min1;
	temp_min1.x=0;
	temp_min1.y=0;
	temp_min1.z=0;

	Vector3 d2;
	d2.x=0;
	d2.y=0;
	d2.z=0;

	for(int i=0; i<(object1->m_bounding_box)->length(); i++){
		
		temp_min = (object1->m_bounding_box)[i].crossProduct(d[0]);
		if(d1.x < temp_min.x && d1.y < temp_min.y && d1.z && temp_min.z){
			
			d1=temp_min;
		}
	}

	for(int i=0; i<(object2->m_bounding_box)->length(); i++){
		
		temp_min1 = (object2->m_bounding_box)[i].crossProduct(d[0]);
		if(d1.x < temp_min1.x && d1.y < temp_min1.y && d1.z && temp_min1.z){
			
			d2=temp_min1;
		}
	}

	//now i have in d1 e d2 the maximum distance for the object1 and 2 and i calculate the SF(d)

	simplex[0].x = d1.x - d2.x;
	simplex[0].y = d1.y - d2.y;
	simplex[0].z = d1.z - d2.z;
	
	
}

void GJK::calculateDistance(){

	//calculate d = -simplex
	d[0].x= (-simplex[0].x);
	d[0].y = (-simplex[0].y);
	d[0].z = (-simplex[0].z);
}

bool GJK::findIfTheyCollide(){
	Vector3 temp;

	//calculate the 0-simplex
	updateSimplex();	
	calculateDistance();
	while(true){
		//copy the data in the next position
		simplex[2] = simplex[1];
		simplex[1] =simplex[0];
		//simplex 1
		updateSimplex();
		//step 5 
		if(simplex[0].dotProduct(d[0]) > 0){
			return false;
		}
		//linear equation in a 3d space: z=ax+by+d
		calculateDistance();
		int y,z,t;

		t = -simplex[0].x / (simplex[1].x - simplex[0].x);
		y = simplex[0].y + (simplex[1].y - simplex[0].y) * t;
		z = simplex[0].z + (simplex[1].z - simplex[0].z) * t;

		if((y == 0) && ( z == 0))
			return true;

		//case 7
		Vector3 temp1;
		temp = simplex[0] - simplex[1];
		temp1.x = - simplex[0].x;
		temp1.y = - simplex[0].y;
		temp1.z = - simplex[0].z;

		if(temp.dotProduct(temp1)>0){
			simplex[2] = simplex[1];
			simplex[1] = simplex[0];
			updateSimplex(); 
			calculateDistance();
		}else{

			temp = Vector3::ZERO;
			Vector3 perpendicular_vector;
			//ABXAO
			temp = (simplex[0]-simplex[1]).crossProduct(simplex[0]);
			//AB X AO X AB
			perpendicular_vector = temp.crossProduct(simplex[0] - simplex[1]);
			if(perpendicular_vector.dotProduct(simplex[0])>0){
				d[0] = perpendicular_vector;
				break;
			}else{
				//AB X -AO
				temp = (simplex[0]-simplex[1]).crossProduct(Vector3::ZERO - simplex[0]);
				// AB X -AO X AB
				perpendicular_vector = temp.crossProduct(simplex[0] - simplex[1]);
				if(perpendicular_vector.dotProduct(simplex[0])>0){
				
					d[0] = perpendicular_vector;
					break;
				}
		}
	}
}