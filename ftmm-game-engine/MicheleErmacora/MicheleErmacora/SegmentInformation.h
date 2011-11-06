#include "EAllocationType.h"

struct SegmentInformation{
	
	//information about the next position of the segment
	unsigned int next_free_segment;
	//type of the segment (physics, ai, ...)
	EAllocationType allocation_type;
	//the block is free or not?
	EIsAvailable is_available; 
	//dimension of the segment
	unsigned int dimension;
};