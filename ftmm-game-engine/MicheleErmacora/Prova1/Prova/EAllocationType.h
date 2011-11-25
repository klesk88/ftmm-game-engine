

/*
	Types of objects that the memory can allocate
	and if the block is a free block or a used block
*/
enum EAllocationType
	{
		NO_ASSIGNED,
		PHYSICS,
		AI,
		RENDERING,
		NODES,
		FREE_STRUCTURE,
	};

enum EIsAvailable{

		FREE,
		USED,
	};

