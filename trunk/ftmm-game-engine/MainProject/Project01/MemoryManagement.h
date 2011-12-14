#ifndef MemoryManagement__H
#define MemoryManagement__H

#pragma once //singletone
#include <tchar.h>

#include "RegionInformation.h"
#include <stdio.h>//imprt for overwrite the new operator
#include <stdlib.h> //for exit the program

//declarations of variables
static long page_size=0;
static long  region_size=0;
static unsigned long  size_segment_information=sizeof(SegmentInformation);

//declarations of functions
static inline void* operator new (size_t size,EAllocationType inf);
static SegmentInformation*  createSegment(RegionInformation** reserved_memory,EAllocationType inf,size_t size);
static long  initializePageSize();
static long initializeRegionSize();
static bool  getMemoryFromSystem(RegionInformation** region,size_t size,HANDLE base_reserved);
static bool  reserveMemory(RegionInformation** region, unsigned long size_to_reserve);
static inline void  operator delete(void* obj, EAllocationType inf);

//code for the functions

static inline void* operator new (size_t size,EAllocationType inf){
	
	//const int inf = EAllocationType::NO_ASSIGNED;
	SegmentInformation* segment(nullptr);
	static RegionInformation* reserved_memory(nullptr);
	//static unsigned long free_structure_dimension = sizeof(FreeSegmentStructure);
	
	HANDLE memory_position(nullptr);
	HANDLE result(nullptr);
	size_t size_to_allocate=0;
	size_t size_commited=0;
	static bool to_be_initialized=true;
	bool enter=false;
	
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
	}

	size_to_allocate = size+size_segment_information;//size + size_segment_information;
	RegionInformation* check = reserved_memory;
	while(check->previous_region!=nullptr){
		
		SegmentInformation* search = reserved_memory->last_free_segment;
		while(search!= nullptr && check->maximum_free_dimension >= size){
			
			if(search->is_available == FREE && search->dimension >=size){
				
				size_t free_size = search->dimension - (size);
				int a =  search->dimension;
				//increment the number of objects in that region
				check->count_of_objects +=1;
				search->allocation_type=inf;
				search->dimension = size;
				search->is_available = USED;
				result = search->object_start_position;
			
				//if the dimension of the segment is more big, i have to create nother segment with the information for find it
				if(free_size > size_segment_information){
							
					SegmentInformation* temp = (SegmentInformation*) ((long)search->object_start_position + size);
					temp->segment_start_position = temp;
					temp->region_position = search->region_position;
					temp->dimension = free_size - size_segment_information;
					temp->allocation_type = inf;
					temp->is_available = FREE;
					temp->next_segment = search->next_segment;
					temp->previous_segment  = search->previous_segment;
					temp->object_start_position = (HANDLE)((long)temp + size_segment_information);
					//check if i'm in the last free block pinted by my structure
					if(search->previous_segment!= nullptr){
						search->previous_segment->next_segment = temp;
					}
					//check if i'm in the first free block pinted by my structure
					if(search->next_segment!= nullptr){
						search->next_segment->previous_segment = temp;
						//if it's the first block poiint by my structure i update the pointer
					}else{
						
						check->last_free_segment = temp;
					}
					search->next_segment = nullptr;
					search->previous_segment = nullptr;
					return result;
					}else{
						//update the pointers
						if(search->previous_segment!=nullptr){
							search->previous_segment->next_segment = search->next_segment;
						}
						if(search->next_segment!=nullptr){
							search->next_segment->previous_segment = search->previous_segment;
						}else{
						
							check->last_free_segment = search->previous_segment;
						}
						search->next_segment = nullptr;
						search->previous_segment = nullptr;
				
						return result;
				}
			
			}
			search = search->previous_segment;
			
		}
		check = check->previous_region;
	}
	
	//i check if there is enough space for all the object to be stored in a contigous section of memory inside the actual region, if not i create a new structure
	if(((long)reserved_memory->top_reserved - (long)reserved_memory->actual_committed)<size_to_allocate){
		long region_size_to_allocate=0;
		//with dynamic structures, can happen that the size to allocate is more big than the actual region size
		if(size_to_allocate>region_size) {
		
			int temp = 0;
			temp = size_to_allocate/region_size;
			if(size_to_allocate%region_size!=0){
				long temp1 = region_size;
				region_size_to_allocate = temp1 + (region_size * temp);
			}else{
				region_size_to_allocate = region_size * temp;
			}
		}else{
		
			region_size_to_allocate = region_size;
		}
		reserveMemory(&reserved_memory,region_size_to_allocate);
		result=VirtualAlloc (reserved_memory->actual_committed, (page_size),MEM_COMMIT, PAGE_READWRITE);
		if(!result){
			_tprintf(TEXT("Failed to commit the object in the heap with LastError %d.\n"), GetLastError());
			exit(1); 
		}
	}
	size_commited = ((long)reserved_memory->top_committed - (long) reserved_memory->actual_committed);
		//because i have to allocate at least 4096 bytes, i check if i have space in the page that i have allocate before
	if(size_commited > size_segment_information){
			

			
			if(size_commited > size_to_allocate){
				size_commited  = size_to_allocate;
			}

			segment=createSegment(&reserved_memory,inf,size);
			reserved_memory->actual_committed = (HANDLE)((unsigned long)reserved_memory->actual_committed + size_commited ); 
			size_to_allocate -=size_commited;
			enter=true;
			//return result;
		}
		//i have enough space in the region but not commited only reserved
		if(((long)reserved_memory->top_reserved - (long)reserved_memory->top_committed)>0 && size_to_allocate!=0){
				
				//i have to see how many times it stays in the pagesize because the virtaul allocate can allocate only for the pagesize
				int j = (size_to_allocate / page_size);
				int i=1;
				do{
					result=VirtualAlloc (reserved_memory->top_committed, (page_size),MEM_COMMIT, PAGE_READWRITE);
					if(!result){
						_tprintf(TEXT("Failed to commit the object in the heap with LastError %d.\n"), GetLastError());
						exit(1); 
					}
			
					if(size_to_allocate>page_size){
						size_commited=page_size;
					}else{
						size_commited=size_to_allocate;
					}

					if(!enter){
			
						segment=createSegment(&reserved_memory,inf,size);
						enter=true;
					}
					
					reserved_memory->actual_committed = (HANDLE)((unsigned long) reserved_memory->actual_committed + size_commited);
					reserved_memory->top_committed = (HANDLE)((unsigned long)reserved_memory->top_committed + page_size ); 
					//how  much memory remain i have to allocate
					size_to_allocate -= size_commited;
					i++;
				}while(i<=j && ((long)reserved_memory->top_reserved - (long) reserved_memory->top_committed) > 0);
				//if the object to allocate wasn´t exactly dividable by the pagesize, i have some other bytes to allcoate (gived by the rest of the division)
				//i allocate them now
				if(size_to_allocate !=0 && ((long)reserved_memory->top_reserved - (long) reserved_memory->top_committed) > 0){

					size_commited = size_to_allocate;
					result=VirtualAlloc (reserved_memory->top_committed, (page_size),MEM_COMMIT, PAGE_READWRITE);
					reserved_memory->actual_committed = (HANDLE)((unsigned long) reserved_memory->actual_committed + size_commited);
					reserved_memory->top_committed = (HANDLE)((unsigned long)reserved_memory->top_committed + page_size );
					size_to_allocate -=size_commited;
				}				
			}
		//or i have to create a new region
	reserved_memory->count_of_objects += 1;
	result = segment->object_start_position;
	return result;
}

static SegmentInformation*  createSegment(RegionInformation** reserved_memory,EAllocationType inf,size_t size){

	SegmentInformation* segment;

	segment = (SegmentInformation*)(*reserved_memory)->actual_committed;
	segment->region_position = *reserved_memory;
	segment->allocation_type = inf;
	segment->dimension = size;
	segment->is_available = USED;
	segment->object_start_position = (HANDLE)((unsigned long)(*reserved_memory)->actual_committed + size_segment_information);
	segment->segment_start_position = (*reserved_memory)->actual_committed;
	return segment;
}

static long  initializePageSize(){

	 SYSTEM_INFO system_info;
		GetSystemInfo (&system_info);
		return system_info.dwPageSize;
}

static long initializeRegionSize(){

		SYSTEM_INFO system_info;
		GetSystemInfo (&system_info);
		return system_info.dwAllocationGranularity;   
}

static bool  getMemoryFromSystem(RegionInformation** region,size_t size,HANDLE base_reserved){
	RegionInformation* next_Region(nullptr);
	//Allocates a block of memory from a heap. The allocated memory is not movable.
	HANDLE temp = HeapAlloc(GetProcessHeap(),HEAP_GENERATE_EXCEPTIONS,sizeof(RegionInformation));
	//check for consistency
	if(!temp){
		_tprintf(TEXT("Failed to create the region structure LastError %d.\n"), GetLastError());
		//exit(1); 
	}
	next_Region = (RegionInformation*) temp;
	next_Region->region_start_position = base_reserved;
	next_Region->count_of_objects = 0;
	next_Region->actual_committed = base_reserved;
	next_Region->previous_region = *region;
	next_Region->last_free_segment = nullptr;
	next_Region->maximum_free_dimension = 0;
	if(*region != nullptr){
		(*region)->next_region = next_Region;
	}
	next_Region->next_region = nullptr;
	next_Region->reserve_size = size; 
	next_Region->top_committed = base_reserved;
	next_Region->top_reserved = (HANDLE)((unsigned long) base_reserved + size);
	
	
	//region became the actual new region of memory
	*region = next_Region;
	return true;
}

static bool  reserveMemory(RegionInformation** region, unsigned long size_to_reserve){
	bool found=false;
	MEMORY_BASIC_INFORMATION memory_info;
	void *base_reserved(nullptr);
	SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
	static bool c = true;
	
	memory_info.BaseAddress = (* region)->top_reserved;
	
/*
 MEMORYSTATUSEX statex;

	 statex.dwLength = sizeof (statex);

	 GlobalMemoryStatusEx (&statex);
	  _tprintf (TEXT("There is  %*ld percent of memory in use.\n"),
            WIDTH, statex.dwMemoryLoad);
  _tprintf (TEXT("There are %*I64d total Kbytes of physical memory.\n"),
            WIDTH, statex.ullTotalPhys/DIV);
  _tprintf (TEXT("There are %*I64d free Kbytes of physical memory.\n"),
            WIDTH, statex.ullAvailPhys/DIV);
  _tprintf (TEXT("There are %*I64d total Kbytes of paging file.\n"),
            WIDTH, statex.ullTotalPageFile/DIV);
  _tprintf (TEXT("There are %*I64d free Kbytes of paging file.\n"),
            WIDTH, statex.ullAvailPageFile/DIV);
  _tprintf (TEXT("There are %*I64d total Kbytes of virtual memory.\n"),
            WIDTH, statex.ullTotalVirtual/DIV);
  _tprintf (TEXT("There are %*I64d free Kbytes of virtual memory.\n"),
            WIDTH, statex.ullAvailVirtual/DIV);

  // Show the amount of extended memory available.

  _tprintf (TEXT("There are %*I64d free Kbytes of extended memory.\n"),
            WIDTH, statex.ullAvailExtendedVirtual/DIV);
			*/
	while (VirtualQuery (memory_info.BaseAddress, &memory_info, sizeof (MEMORY_BASIC_INFORMATION))) {
	// Region is free, well aligned and big enough: we are done 
	  if (memory_info.State == MEM_FREE &&  (unsigned) memory_info.BaseAddress % size_to_reserve == 0 && memory_info.RegionSize >= size_to_reserve) {
		
		 found = true;
		 //reserve the memory
		 base_reserved = VirtualAlloc (memory_info.BaseAddress, size_to_reserve, MEM_RESERVE, PAGE_NOACCESS);
		 break;
		  
		}
	  memory_info.BaseAddress = (char *) memory_info.BaseAddress + memory_info.RegionSize;
	}
	if(!found){
	
		 base_reserved = VirtualAlloc (nullptr, size_to_reserve, MEM_RESERVE, PAGE_NOACCESS);
	}
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

static inline void  operator delete(void* obj, EAllocationType inf){
	HANDLE t = (HANDLE)((unsigned long)obj - sizeof(SegmentInformation));
	SegmentInformation* segment= (SegmentInformation*)((unsigned long)obj - sizeof(SegmentInformation));
	//static SegmentInformation* previous_free_segment(nullptr);
	RegionInformation* region = (RegionInformation*)(segment->region_position);
	//Fills a block of memory with zeros.
	//ZeroMemory(segment->object_start_position,(segment->dimension-1));
	((RegionInformation*)(segment->region_position))->count_of_objects -=1;

	
	if(((RegionInformation*)(segment->region_position))->last_free_segment == nullptr){

		segment->previous_segment = nullptr;		
	}else{
		
		//if i deallocate an entire region or there aren´t any objects left in the actual region
		if(segment->dimension >= region_size || ((RegionInformation*)(segment->region_position))->count_of_objects == 0){
			//i have to find the poistion of the segemnt containing the inforamtion for this region and delete it from the free structure
						
			//ZeroMemory(segment->region_position,sizeof(RegionInformation)-1);
			VirtualFree(((RegionInformation*)(segment->region_position))->region_start_position,region_size,MEM_RELEASE);
			VirtualFree(((RegionInformation*)(segment->region_position)),sizeof(RegionInformation),MEM_RELEASE);	
			return;
		}
		//check if there is a segment contiguous with this
		SegmentInformation* temp = ((RegionInformation*)(segment->region_position))->last_free_segment;
		while(temp->previous_segment!= nullptr){
			//if the actual segment is in frontof an other free segment
			if (((long)temp->object_start_position + temp->dimension) - ((long) segment->segment_start_position)==0){
				if(temp->is_available != FREE){
					break;
				}
				//update the dimension of the free segment
				temp->dimension += segment->dimension + size_segment_information;
				//ZeroMemory(segment, sizeof(SegmentInformation)-1);
				
				if(((RegionInformation*)(segment->region_position))->maximum_free_dimension < temp->dimension){
	
					((RegionInformation*)(segment->region_position))->maximum_free_dimension = temp->dimension;
				}

				segment = nullptr;
				return;
			}
			//if the actual segment is behind another free segment
			if(((long)temp->segment_start_position) - ((long) segment->object_start_position + segment->dimension)==0){
				if(temp->is_available != FREE){
					break;
				}
				segment->dimension += temp->dimension + size_segment_information;
				segment->is_available = FREE;
				segment->previous_segment = temp->previous_segment;
				//if is the block point by the free structure
				if(temp->next_segment == nullptr){
				
					((RegionInformation*)(segment->region_position))->last_free_segment = segment;
				}
				segment->next_segment = temp->next_segment;
				segment->allocation_type = EAllocationType::NO_ASSIGNED;
				temp->previous_segment->next_segment = segment;
			
				if(((RegionInformation*)(segment->region_position))->maximum_free_dimension < segment->dimension){
	
					((RegionInformation*)(segment->region_position))->maximum_free_dimension = segment->dimension;
				}

				temp = nullptr;
				return;
			
			}
			temp = temp->previous_segment;
		}
		// if i'm not in the first allcoation for the free segment
		
		segment->previous_segment = ((RegionInformation*)(segment->region_position))->last_free_segment;
		((RegionInformation*)(segment->region_position))->last_free_segment->next_segment = segment;
		
		
	}
	
	segment->allocation_type = EAllocationType::NO_ASSIGNED;
	segment->is_available = FREE;
	segment->next_segment = nullptr;
	((RegionInformation*)(segment->region_position))->last_free_segment = segment;
	if(((RegionInformation*)(segment->region_position))->maximum_free_dimension < segment->dimension){
	
		((RegionInformation*)(segment->region_position))->maximum_free_dimension = segment->dimension;
	}
}

#endif