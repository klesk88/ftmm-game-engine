#pragma once //singletone
#include <tchar.h>
#include "RegionInformation.h"
//#include "FreeMemory.h"
//#include <Windows.h>
#include <stdio.h>//imprt for overwrite the new operator
//#include <hash_set>
//#include <iostream>
#include <stdlib.h> //for exit the program
#include <map>
#include"SegmentInformation.h"
//#include "EAllocationType.h"

using namespace std;


//METHODS DECLARATION
inline void* operator new (size_t);
inline void operator delete(void* );
//initialize the dimension of the region
long initializeRegionSize();

long initializePageSize();
//request to the OS for new space
bool getMemoryFromSystem(RegionInformation** region,long size,HANDLE base_reserved);
//initialize the structure for the free memory;
void initializeFreeHeap();

bool reserveMemory(RegionInformation** region, unsigned long size_to_reserve);




//VARIABLE DECLARATONS
// hash_set<int> Set;
//static FreeMemory* free_segments;
//map<unsigned long,SegmentInformation*> free_memory_heap;

SegmentInformation* first_free_segment;


//inline function

inline void* operator new (size_t size){
	
	EAllocationType inf = NO_ASSIGNED;
	SegmentInformation* segment(nullptr);
	static RegionInformation* reserved_memory(nullptr);
	static long region_size=0, page_size=0;
	//static unsigned long free_structure_dimension = sizeof(FreeSegmentStructure);
	static unsigned long size_segment_information = sizeof(SegmentInformation);
	HANDLE memory_position(nullptr);
	HANDLE result(nullptr);
	size_t size_to_allocate=0;
	static bool to_be_initialized=true;

	if(to_be_initialized){
	
		region_size=initializeRegionSize();
		page_size=(initializePageSize());
		
		if(!getMemoryFromSystem(&reserved_memory,0,nullptr)){
			exit(1); 
		}
		
		if(!reserveMemory(&reserved_memory,region_size))
			exit(1); 
		//initializeFreeHeap();
		
		//free_memory_heap.insert(pair<unsigned long,SegmentInformation*>(0,segment));
		//free_memory_heap.clear();
		result=VirtualAlloc (reserved_memory->top_committed, (page_size),MEM_COMMIT, PAGE_READWRITE);
		if(!result){
			_tprintf(TEXT("Failed to commit the object in the heap with LastError %d.\n"), GetLastError());
			exit(1); 
		}
		to_be_initialized=false;
		first_free_segment = (SegmentInformation*)result;
		first_free_segment->allocation_type = FREE_STRUCTURE;
		first_free_segment->dimension = size_segment_information;
		first_free_segment->is_available = USED;
		first_free_segment->object_start_position = reserved_memory->actual_committed;
		first_free_segment->previous_segment = nullptr;
		first_free_segment->next_segment = nullptr;
		first_free_segment->segment_start_position = reserved_memory->actual_committed;
		reserved_memory->top_committed = (HANDLE)((unsigned long)reserved_memory->top_committed + page_size); 
		reserved_memory->actual_committed = (HANDLE)((unsigned long)reserved_memory->actual_committed + size_segment_information ); 
	}

	size_to_allocate = size+size_segment_information;//size + size_segment_information;
	
	if(first_free_segment->next_segment!=nullptr){
		
		SegmentInformation* search = first_free_segment->next_segment;
		while(search->next_segment != nullptr){
		
			if(search->is_available == FREE && search->dimension >=size){
				
				search->allocation_type=inf;
				search->dimension = size;
				search->is_available = USED;
				result = search->object_start_position;
				//update the pointers
				//if i´m not pointing the first free segment
				search->previous_segment->next_segment = search->next_segment;
				search->next_segment->previous_segment = (SegmentInformation*)search->previous_segment->segment_start_position;
				return result;
			}
			search = search->next_segment;
		}
	}
	//because i have to allocate at least 4096 bytes, i check if i have space in the page that i have allocate before
	if(((unsigned long)reserved_memory->top_committed - (unsigned long) reserved_memory->actual_committed) >=size_to_allocate){
		
		segment = (SegmentInformation*) (HANDLE)((unsigned long)reserved_memory->actual_committed);
		segment->allocation_type = inf;
		segment->dimension = size;
		segment->is_available = USED;
		segment->object_start_position = (HANDLE)((unsigned long)reserved_memory->actual_committed + size_segment_information);
		segment->segment_start_position = reserved_memory->actual_committed;
		result = segment->object_start_position;
		reserved_memory->actual_committed = (HANDLE)((unsigned long)reserved_memory->actual_committed + size_to_allocate ); 
		return result;
	}else{
		//i have enough space in the region but not commited only reserved
		if(((unsigned long)reserved_memory->top_reserved - (unsigned long)reserved_memory->top_committed)>=size_to_allocate){
			size_t size_commited=0;
			
			//i check what is the major size between the object to allocate and the page_size: if the object to allocate is more big,
			//i have to see how many times it stays in the pagesize because the virtaul allocate can allocate only for the pagesize
			int j = (size_to_allocate / page_size);//for don´t divide per 0
			if(j==0)
				j=1;
			int i=1;
			do{
				result=VirtualAlloc (reserved_memory->top_committed, (page_size),MEM_COMMIT, PAGE_READWRITE);
				if(!result){
					_tprintf(TEXT("Failed to commit the object in the heap with LastError %d.\n"), GetLastError());
					exit(1); 
				}
			
				if(size_to_allocate>page_size){
					size_commited=page_size;
				}

				reserved_memory->actual_committed = (HANDLE)((unsigned long) reserved_memory->actual_committed + size_commited);
				reserved_memory->top_committed = (HANDLE)((unsigned long)reserved_memory->top_committed + page_size ); 
				//how  much memory remain i have to allocate
				size_to_allocate -= size_commited;
				i++;
			}while(i<j);
			//if the object to allocate wasn´t exactly dividable by the pagesize, i have some other bytes to allcoate (gived by the rest of the division)
			//i allocate them now
			if(size_to_allocate !=0){
			
				segment = (SegmentInformation*) (HANDLE)((unsigned long)reserved_memory->actual_committed);
				segment->allocation_type = inf;
				segment->dimension = size;
				segment->is_available = USED;
				segment->object_start_position = (HANDLE)((unsigned long)reserved_memory->actual_committed + size_segment_information);
				segment->segment_start_position = reserved_memory->actual_committed;
				result = segment->object_start_position;
				reserved_memory->actual_committed = (HANDLE)((unsigned long)reserved_memory->actual_committed + size_to_allocate ); 
			
			}
			return result;
		}
		//or i have to create a new region
		else{

			reserveMemory(&reserved_memory,region_size);
			result=VirtualAlloc (reserved_memory->actual_committed, (size_to_allocate),MEM_COMMIT, PAGE_READWRITE);
			if(!result){
				_tprintf(TEXT("Failed to commit the object in the heap with LastError %d.\n"), GetLastError());
				exit(1); 
			}
			//TO CHANGE
			if(to_be_initialized){
				
			}
			segment = (SegmentInformation*) (HANDLE)((unsigned long)reserved_memory->actual_committed);
				segment->allocation_type = inf;
				segment->dimension = size;
				segment->is_available = USED;
				segment->object_start_position = (HANDLE)((unsigned long)reserved_memory->actual_committed + size_segment_information);
				segment->segment_start_position = reserved_memory->actual_committed;
				result = segment->object_start_position;
			reserved_memory->actual_committed = (HANDLE)((unsigned long)reserved_memory->actual_committed + size_to_allocate);
			reserved_memory->top_committed = (HANDLE)((unsigned long)reserved_memory->top_committed + page_size); 
		}
	}
	return result;
}



long initializePageSize(){

	 SYSTEM_INFO system_info;
		GetSystemInfo (&system_info);
		return system_info.dwPageSize;
}

long initializeRegionSize(){

		SYSTEM_INFO system_info;
		GetSystemInfo (&system_info);
		return system_info.dwAllocationGranularity;   
}

bool getMemoryFromSystem(RegionInformation** region,long size,HANDLE base_reserved){
	RegionInformation* next_Region(nullptr);

	HANDLE temp = HeapAlloc(GetProcessHeap(),HEAP_GENERATE_EXCEPTIONS,size);
	next_Region = (RegionInformation*) temp;
	//check for consistency
	if(!temp){
		_tprintf(TEXT("Failed to create the region structure LastError %d.\n"), GetLastError());
		//exit(1); 
	}
	next_Region->actual_committed = base_reserved;
	next_Region->previous_region = *region;
	//(*region)->next_region = next_Region;
	next_Region->reserve_size = size; 
	next_Region->top_committed = base_reserved;
	next_Region->top_reserved = (HANDLE)((unsigned long) base_reserved + size);
	
	
	//region became the actual new region of memory
	*region = next_Region;
	return true;
}

bool reserveMemory(RegionInformation** region, unsigned long size_to_reserve){
	bool found=false;
	bool contigous = true;
	MEMORY_BASIC_INFORMATION memory_info;
	void *base_reserved(nullptr);

	memory_info.BaseAddress = (* region)->top_reserved;
	while (VirtualQuery (memory_info.BaseAddress, &memory_info, sizeof (memory_info))) {
	// Region is free, well aligned and big enough: we are done 
	  if (memory_info.State == MEM_FREE &&  (unsigned) memory_info.BaseAddress % size_to_reserve == 0 && memory_info.RegionSize >= size_to_reserve) {
		 found = true;
		  break;
		}
	  memory_info.BaseAddress = (char *) memory_info.BaseAddress + memory_info.RegionSize;
	}
	//reserve the memory
	base_reserved = VirtualAlloc (memory_info.BaseAddress, size_to_reserve, MEM_RESERVE, PAGE_NOACCESS);
	//check for consistency
	if(!base_reserved){
		_tprintf(TEXT("Failed to extend the heap with LastError %d.\n"), GetLastError());
		exit(1); 
	}
	//create my structure
	if(!getMemoryFromSystem(region,size_to_reserve,base_reserved)){
		exit(1);
	}
	return true;
}

inline void operator delete(void* obj){
	bool set=false;
	long b= sizeof(SegmentInformation);
	HANDLE t = (HANDLE)((unsigned long)obj - sizeof(SegmentInformation));
	SegmentInformation* segment= (SegmentInformation*)((unsigned long)obj - sizeof(SegmentInformation));
	static SegmentInformation* previous_free_segment(nullptr);

	if(first_free_segment->next_segment == nullptr){

		segment->previous_segment = first_free_segment;
		first_free_segment->next_segment = segment;

		
	}else{
		segment->previous_segment = previous_free_segment;
		previous_free_segment->next_segment = segment;
		
	}
	
	segment->allocation_type = NO_ASSIGNED;
	segment->is_available = FREE;
	segment->next_segment = nullptr;
	previous_free_segment=segment;
	
}