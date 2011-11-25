
#pragma once //singletone
#include <tchar.h>
#include "SegmentInformation.h"
#include <Windows.h>
#include <stdio.h>//imprt for overwrite the new operator

//To enable the low-fragmentation heap when running under a debugger, set the _NO_DEBUG_HEAP environment variable to 1.
#define _NO_DEBUG_HEAP 1;
#define CEIL(size,to)	(((size)+(to)-1)&~((to)-1))
#define FLOOR(size,to)	((size)&~((to)-1))
	/*void * operator new (unsigned int size);
	void * operator new[] (unsigned int size);
	void operator delete(void *p);
	void operator delete[] (void * p);
	*/

	//variable that tell if the initial heap is been allocated or not
	bool initialize(false);
	bool debug(true);
	//variable that store the intial memory address
	HANDLE managed_memory_start(nullptr);
	HANDLE last_valid_address(nullptr);
	SegmentInformation* start_segment(nullptr);
	static long page_size=0, my_page_size=0;
	static long region_size=0, my_region_size=0;

	
	//void*  operator new (size_t size);


	static int g_sl;
	/* Wait for spin lock */
	
	int slwait (int *sl) {
	
		while (InterlockedCompareExchange ((LPLONG ) sl,  1,  0) != 0) 
		Sleep (0);
		return 0;
	}	
	/* Release spin lock */
	
	int slrelease (int *sl) {
		InterlockedExchange ((LPLONG)sl, 0);
		return 0;
	}


	/* getpagesize for windows */
	long getPageSize (void) {
		static long g_pagesize = 0;
		if (! g_pagesize) {
			SYSTEM_INFO system_info;
			GetSystemInfo (&system_info);
			g_pagesize = system_info.dwPageSize;
		}
		return g_pagesize;
	}

	//get regionsize
	long getRegionSize (void) {
		static long g_regionsize = 0;
		if (! g_regionsize) {
			SYSTEM_INFO system_info;
			GetSystemInfo (&system_info);
			g_regionsize = system_info.dwAllocationGranularity;
		}
		return g_regionsize;
	}

	typedef struct _region_entry{
	
			HANDLE top_allocated;
			HANDLE top_commited;
			HANDLE top_reserved;
			HANDLE last_free_segment;
			long reserve_size;
			struct _region_entry *previus;
	} region_entry;

	static bool region_entry_append(region_entry** last,void* base_reserved,long reserve_size){
	
		region_entry *next = (region_entry *)HeapAlloc(GetProcessHeap(),HEAP_GENERATE_EXCEPTIONS,sizeof(region_entry));
		
		if(!next)
			return false;

		next->reserve_size = reserve_size;
		//handle indicating the last position of the last free segment used for make the back pointer when i connect a new free segment
		next->last_free_segment = nullptr;
		//points to the top of (application) allocated memory in the committed area
		next->top_allocated = base_reserved;
		//top of the committed memory in the reserved chunk
		next->top_commited =base_reserved;
		//top address
		next->top_reserved=base_reserved;
		next->previus = *last;
		*last=next;
		return true;
	}


	//declaration of methods;
	HANDLE allocateMemory (size_t allocate_size, region_entry** reg_entry,EAllocationType);

	//initialization of the heap
	int initializationMemory(){

		// http://msdn.microsoft.com/en-us/library/windows/desktop/aa366705%28v=vs.85%29.aspx
		/*
			Because the system cannot compact a private heap, it can become fragmented. Applications that allocate large amounts of memory in various allocation 
			sizes can use the low-fragmentation heap to reduce heap fragmentation.
		*/

		bool bResult = false;
		ULONG HeapInformation=2;

	
		bResult = HeapSetInformation(NULL,
                                 HeapEnableTerminationOnCorruption,
                                 NULL,
                                 0);

		 if (bResult != false) {
				 _tprintf(TEXT("Heap terminate-on-corruption has been enabled.\n"));
		  }
		  else {
				_tprintf(TEXT("Failed to enable heap terminate-on-corruption with LastError %d.\n"),
						  GetLastError());

				return 1;
		  }

		 // Enable the low-fragmenation heap (LFH). Starting with Windows Vista, 
		 // the LFH is enabled by default but this call does not cause an error.
		 //
		bResult=true;  
		/*
		HeapInformation = (ULONG)2; //value for enabling LFH
		bResult = HeapSetInformation(GetProcessHeap(),
								    HeapCompatibilityInformation,
								    &HeapInformation,
			  						sizeof(HeapInformation));
		  if (bResult != true) {
		 	  _tprintf(TEXT("The low-fragmentation heap has been enabled.\n"));
		  }
		   else {
			   _tprintf(TEXT("Failed to enable the low-fragmentation heap with LastError %d.\n"),
			 		  GetLastError());

			   return 1;
		  }
		*/
		  return 0;
		
	}
	static region_entry* reg_entry(nullptr);
	//rewrite the new operator
	void*    new1 (size_t size){
		
		HANDLE search_position(nullptr);
		void* memory_position(nullptr);
		SegmentInformation* segment(nullptr);
		EAllocationType inf = NO_ASSIGNED;
		size_t allocation_size=0;
		
	
		
		//spinlock 
		slwait(&g_sl);

		
		
		//if the memory is not initialized initialized it
		if(!initialize){
		
			initializationMemory();
			   //initiliaze region of memory
			
			if(!region_entry_append(&reg_entry,0,0)){
		  
			_tprintf(TEXT("Failed to initialize the region with LastError %d.\n"),
			 		  GetLastError());
			   return 0;
			}
			//managed_memory_start=reg_entry;
			//last_valid_address = reg_entry;
			initialize=true;
		}
		
		//calculate the toal amount of emmroy necessaty for the object created with my structure in it
		allocation_size = size + sizeof(SegmentInformation);
		
		
			//i start to search from the last free segments backwards
			search_position=reg_entry->last_free_segment;
			memory_position=0;
			/*
			while(search_position != nullptr){
				segment=(SegmentInformation*)(search_position); 
				//check if the position in the memory is available 
				if(segment->is_available==FREE){
					//check if the dimension of the block is enough
					//THIS IS WHERE I HAVE TO PUT MY POLITICS OF FIT IN THE MEMORY
					if(segment->dimension >= size){
						
						segment->is_available=USED;		
						segment->allocation_type = inf;
						segment->dimension=size;
						segment->back_free_segment = nullptr;
						segment->next_free_segment = nullptr;
						
						memory_position=(HANDLE)search_position;//own the memory position
							
						break;//leave the loop
					}
				}
				//we don't find a block suitable for us so we move on to the next block
				search_position=(HANDLE)segment->back_free_segment;
			}
			*/
			//if we don't find nothing correctly we ask to the os more memory 
			if(!memory_position){

				memory_position = allocateMemory(size,&reg_entry,inf);
				//check for consistency
				if (memory_position == NULL) {
				  _tprintf(TEXT("Failed to extend the memory with LastError %d.\n"),
						   GetLastError());
				  return 0;
			 }

		}
		//return the pointer from the object on, it doesn't need to know about my structure
		//memory_position=(HANDLE)((unsigned int)memory_position+(unsigned int)sizeof(SegmentInformation));
		//relase the spinlock
		slrelease (&g_sl);
		return memory_position;

	}

	HANDLE allocateMemory (size_t allocate_size, region_entry** reg_entry, EAllocationType inf) {
		HANDLE result(nullptr);
		size_t size=0;
		long to_commit=0;
		long to_reserve=0;
		long commit_size=0;
		SegmentInformation* segment(nullptr);
		//type of allocation: physics,ai,ecc
		EAllocationType type;

		type=inf;
		size=allocate_size + sizeof(SegmentInformation);
		if(!page_size){
			page_size=getPageSize();
			my_page_size = page_size;
		}
		if(!region_size){
			region_size= getRegionSize();
			my_region_size = region_size;
		}
		
		//memory already allocated + the size of the object i have to allocate - the toale amount af data that
		//i have already put in the memory
		to_commit= (long)(*reg_entry)->top_allocated +(long)size - (long)(*reg_entry)->top_commited;
		if(to_commit>0){
			commit_size = CEIL(to_commit,my_page_size);
			//how much to reserve 
			to_reserve = (long)(*reg_entry)->top_commited + commit_size - (long)(*reg_entry)->top_reserved;
			
			if(to_reserve>0){
				//if there is a bit of space but not enough for all the data in the current region
				long remaining_commit_size = (long) (*reg_entry)->top_reserved - (long)(*reg_entry)->top_commited;
				if(remaining_commit_size >0){
				
					HANDLE base_commited = VirtualAlloc((*reg_entry)->top_commited,remaining_commit_size,MEM_COMMIT,PAGE_READWRITE);
					//check for consistency
					if (!base_commited){
					
						 _tprintf(TEXT("Failed to Commit in the memory when there is a small space in my actual region with LastError %d.\n"),
										GetLastError());
						 return 0;
					}

					(*reg_entry)->top_commited = (HANDLE)((long)base_commited + remaining_commit_size);
					segment = (SegmentInformation*) ((long)base_commited + sizeof(SegmentInformation));				
				}
				
			    //let´s check in the memory new zones for us yupieeeeeeeeee
				SYSTEM_INFO system_info;
				MEMORY_BASIC_INFORMATION memory_info;
				//variable that tell me if i find a right position in memory
				bool found=false;
				bool contiguous=true;
				HANDLE base_reserved(nullptr);
				long reserve_size=0;
				do{
					reserve_size =CEIL(to_reserve,my_region_size);
					memory_info.BaseAddress = (*reg_entry)->top_reserved;
					while( VirtualQuery (memory_info.BaseAddress, &memory_info, sizeof (memory_info))){
						 // Region is free, well aligned and big enough: we are done 
						if (memory_info.State == MEM_FREE && (unsigned)memory_info.BaseAddress % region_size ==0 && memory_info.RegionSize >= reserve_size) {
							found = true;
							break;
						}
					    /* From now on we can't get contiguous memory! */
					  contiguous = false;
					  reserve_size = CEIL (size, my_region_size);
					  memory_info.BaseAddress = (char *) memory_info.BaseAddress + memory_info.RegionSize;
					}
					if(!found){
		
						return 0;
					}
			
					base_reserved = VirtualAlloc (memory_info.BaseAddress, reserve_size, MEM_RESERVE, PAGE_NOACCESS);

					if (! base_reserved) {
					 _tprintf(TEXT("Failed to Reserve the pages when i looking for new memory with LastError %d.\n"),
							   GetLastError());
					 return 0;
					}
				}while(!base_reserved);
				//check for consistency
				if (memory_info.BaseAddress && base_reserved != memory_info.BaseAddress)
					return 0;
				//if we have contigous memory
				if(contiguous){
					//subtract from the total size, the size that i have already allcoated
					long start_size = (long)(*reg_entry)->top_commited - (long)(*reg_entry)->top_allocated;
					size -= start_size;
					//the allcoated zone and the commited zone point to the same position
					(*reg_entry)->top_allocated = (*reg_entry)->top_commited;
					to_commit = (long)(*reg_entry)->top_allocated + size - (long)(*reg_entry)->top_commited;
					//round size to commit in  memory
					commit_size = CEIL(to_commit,my_page_size);
				}
				//check for consistency and create the new region

				if(!region_entry_append(&(*reg_entry),base_reserved,reserve_size)){
					_tprintf(TEXT("Failed to create to call region_entry_append for create a new region with LastError %d.\n"),
							   GetLastError());
					 return 0;
				
				}
				
				//if we don´t have contigous memory
				if(!contiguous){
					//recompute the size
					size = (size_t)(*reg_entry)->top_allocated + size - (size_t)(*reg_entry)->top_commited;
					commit_size=CEIL(size,my_page_size);
				}				
			}
			//
			//commit in the memory
			// 
		 
			HANDLE commit = VirtualAlloc ((*reg_entry)->top_commited,commit_size,MEM_COMMIT,PAGE_READWRITE);
			/* Check returned pointer for consistency */
			if (commit != (*reg_entry)->top_commited){
				 _tprintf(TEXT("Failed to create to commit in the memory with LastError %d.\n"),
							   GetLastError());
			    return 0;
			}
		//adjust the  regions commit top
			(*reg_entry)->top_commited = (HANDLE)((long)commit + commit_size);
			
		}
		//adjust allocation top
		(*reg_entry)->top_allocated = (HANDLE)((long)(*reg_entry)->top_allocated + size);
		segment = (SegmentInformation*) ((long)(*reg_entry)->top_allocated);
		//FOR MY STRUCTURE
		segment->is_available=USED;
		segment->next_free_segment=(nullptr);
		segment->back_free_segment = nullptr;
		segment->dimension = allocate_size;
		segment->allocation_type = type;
		//		
		result = (HANDLE)((size_t)(*reg_entry)->top_allocated - size);
		return result;
}
/*
void operator delete(void* obj){
	//point to the previous block
	void* temp = obj;
	SegmentInformation* information(nullptr);
	SegmentInformation* t(nullptr);
	size_t dim  =0;

	t=(SegmentInformation*) temp;
	int rc = VirtualFree (obj, t->dimension + sizeof(SegmentInformation),MEM_RELEASE);

 }//close deallocation fucntion


 */



