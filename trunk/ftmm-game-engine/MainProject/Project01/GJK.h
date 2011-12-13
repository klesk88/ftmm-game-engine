#include "Vector3.h"
#include "Collidable.h"

class GJK{
public:
	GJK(Collidable* collidable1,Collidable* collidable2);
	bool findIfTheyCollide();


private:
	//vector where to store the points for the simplex
	Vector3* simplex;
	//objects that i have to see if they collide or not
	Collidable* object1;
	Collidable* object2;
	//vector where i store the Minkowski figure
	Vector3* shape;
	//function for calculate the Minkowski difference
	void minkowskiDifference();
	//distance variable
	Vector3* d;
	//calculate the distance
	void updateSimplex();

	void calculateDistance();
	

};