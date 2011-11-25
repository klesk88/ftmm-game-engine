
#include <windows.h>


typedef struct _RegionInformation{
	
	//information about the next position of the segment
	struct _RegionInformation* next_region;
	//used if the segment is free pointer backward to the position before
	struct _RegionInformation* previous_region;
	//size of the reserved memory
	unsigned long reserve_size;
	//top commited
	HANDLE top_committed;
	HANDLE actual_committed;
	//top reserved
	HANDLE top_reserved;
}RegionInformation;


