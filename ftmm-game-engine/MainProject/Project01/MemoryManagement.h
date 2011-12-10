#ifndef MemoryManagement__H
#define MemoryManagement__H

#pragma once //singletone
#include <tchar.h>

#include "RegionInformation.h"
#include <stdio.h>//imprt for overwrite the new operator
#include <stdlib.h> //for exit the program

class MemoryManagement{
public:

	inline void* operator new (size_t);
	inline void operator delete(void* );
	MemoryManagement();
	static MemoryManagement* getInstance();
	static EAllocationType inf;
private:

	static inline void* n_new(size_t);
	//initialize the dimension of the region
	static long initializeRegionSize();
	static inline SegmentInformation* createSegment(RegionInformation** reserved_memory,EAllocationType inf,size_t size);
	static long initializePageSize();
	//request to the OS for new space
	static bool getMemoryFromSystem(RegionInformation** region,size_t size,HANDLE base_reserved);
	//initialize the structure for the free memory;
	static void initializeFreeHeap();
	static MemoryManagement* memory;
	static bool reserveMemory(RegionInformation** region, unsigned long size_to_reserve);

	static long region_size;
	static long page_size;
	static unsigned long size_segment_information;
};

#endif