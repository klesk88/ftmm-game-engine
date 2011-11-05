#pragma once //singletone

class NewDelete{
public:
	//void * operator new (unsigned int size);
	void * operator new[] (unsigned int size);
	void operator delete(void *p);
	void operator delete[] (void * p);

	void* operator new (unsigned int size){
	
		void* datapointer;
	
	}

};