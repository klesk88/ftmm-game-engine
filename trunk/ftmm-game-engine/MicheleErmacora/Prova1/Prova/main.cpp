#include<iostream>
#include <time.h>
#include <vector>
using namespace std;



class Complex 
  {
  public:
	  Complex (){};
  private:
  double r; // Real Part
  double c; // Complex Part
  };
  
int main(int argc, char* argv[]) 
  {
	 time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  vector<string> SS;
	 
   SS.push_back("The number is 10");
	std::cout<< asctime (timeinfo)<<'\n';
	Complex* array[1000];
	for (int i = 0;i  <  5000; i++) {
		//cout<<i<<'\n';
		for (int j = 0; j  <  1000; j++) {
			array[j] = new Complex();
			//cout<<j<<'\n';
		}
		
		for (int j = 0; j  <  1000; j++) {
		delete array[j];
      
		  }
		
	 }


//	 seconds = time (NULL)<<'\n';
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	std::cout<< asctime (timeinfo)<<'\n';
	return 0;

}      
