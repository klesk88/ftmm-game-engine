
#include "EAllocationType.h"
#include <windows.h>


typedef struct _SegmentInformation{
	
	//information about the next position of the segment
	struct _SegmentInformation* next_segment;
	//used if the segment is free pointer backward to the position before
	struct _SegmentInformation* previous_segment;
	//type of the segment (physics, ai, ...)
	EAllocationType allocation_type;
	//the block is free or not?
	EIsAvailable is_available; 
	//dimension of the segment
	unsigned long dimension;
	HANDLE object_start_position;

}SegmentInformation;


