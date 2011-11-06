//#include "NewDelete.cpp"

#include <iostream>
#include <string>
using namespace std;

class A{
public:
	void ciao(){
	
		int a=0;
		a=a+1;
	}

};

void main(){
	char* b;
	A* a= new A();
	a->ciao();
	A* d = new A();
	d->ciao();
	cout<<"ciao"<<'\n';
	cin>>b;

}