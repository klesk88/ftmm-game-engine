#pragma once //singletone
#include <windows.h>
#include <tchar.h>
#include "SegmentInformation.h"
#include <stdio.h>//imprt for overwrite the new operator


	/*void * operator new (unsigned int size);
	void * operator new[] (unsigned int size);
	void operator delete(void *p);
	void operator delete[] (void * p);
	*/

	//variable that tell if the initial heap is been allocated or not
	bool initialize(false);
	//variable that store the intial memory address
	HANDLE managed_memory_start;
	HANDLE last_valid_address;
	
	//initialization of the heap
	int initializationMemory(){

		// http://msdn.microsoft.com/en-us/library/windows/desktop/aa366705%28v=vs.85%29.aspx
		/*
			Because the system cannot compact a private heap, it can become fragmented. Applications that allocate large amounts of memory in various allocation 
			sizes can use the low-fragmentation heap to reduce heap fragmentation.
		*/


		bool bResult;
		HANDLE hHeap;
		ULONG HeapInformation;
		

		bResult = HeapSetInformation(NULL,
                                 HeapEnableTerminationOnCorruption,
                                 NULL,
                                 0);

		 if (bResult != FALSE) {
				 _tprintf(TEXT("Heap terminate-on-corruption has been enabled.\n"));
		  }
		  else {
				_tprintf(TEXT("Failed to enable heap terminate-on-corruption with LastError %d.\n"),
						  GetLastError());
				return 1;
		  }

		
	    // Create a new heap with default parameters.
	   
	    hHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS, 0, 0);//second value is the initial size MUST BE CHANGED with a value that allocates enough memory for the intitial startup
		if (hHeap == NULL) {
			  _tprintf(TEXT("Failed to create a new heap with LastError %d.\n"),
					   GetLastError());
			  return 1;
		  }

		 //
		 // Enable the low-fragmenation heap (LFH). Starting with Windows Vista, 
		 // the LFH is enabled by default but this call does not cause an error.
		 //
		HeapInformation = 2; //value for enabling LFH
		bResult = HeapSetInformation(hHeap,
								    HeapCompatibilityInformation,
								    &HeapInformation,
			  						sizeof(HeapInformation));
		  if (bResult != FALSE) {
		 	  _tprintf(TEXT("The low-fragmentation heap has been enabled.\n"));
		  }
		   else {
			   _tprintf(TEXT("Failed to enable the low-fragmentation heap with LastError %d.\n"),
			 		  GetLastError());
			   return 1;
		  }
		  
		  managed_memory_start=hHeap;//obtain the pointer to the memory address
		  last_valid_address=hHeap; //set the last valid address to the actual address
		  initialize=true;//memory is intialized correctly
		  return 0;
		
	}

	//rewrite the new operator

	void* operator new (unsigned int size){
	
		HANDLE search_position;
		HANDLE memory_position;
		SegmentInformation* segment;
		//if the memory is not initialized initialized it
		if(!initialize){
		
			initializationMemory();
		}
		//calculate the toal amount of emmroy necessaty for the object created with my structure in it
		size = size + sizeof(segment);
		search_position=managed_memory_start;
		memory_position=0;
		while(search_position != last_valid_address){
			
			segment=(SegmentInformation*)memory_position; 
			//check if the position in the memory is available
			if(segment->is_available==FREE){
				//check if the dimension of the block is enough
				if(segment->dimension >= size){
				
					segment->is_available=USED;	
					memory_position=search_position;//own the memory position
					break;//leave the loop
				}
			}
			//we don't find a block suitable for us so we move on to the next block
			search_position=(HANDLE)segment->next_free_segment;
		}
		//if we don't find nothing correctly we ask to the os more memory
		if(!memory_position){
			//alloc new memory in the heap with the right dimension
			memory_position=HeapAlloc(managed_memory_start,HEAP_ZERO_MEMORY,size);
			if (memory_position == NULL) {
			  _tprintf(TEXT("Failed to extend the heap with LastError %d.\n"),
					   GetLastError());
			  return 0;
		  }

			//i need to change the values in my segment information
			segment=(SegmentInformation*)memory_position;
			segment->next_free_segment=(unsigned int)memory_position+size;
			segment->dimension=size;
			segment->is_available=USED;
		}
		//return the pointer from the object on, it doesn't need to know about my structure
		memory_position=(HANDLE)((unsigned int)memory_position+(unsigned int)sizeof(SegmentInformation));
		return memory_position;

	}



