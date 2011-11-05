/*
	Types of objects that the memory can allocate
	and if the block is a free block or a used block
*/

enum EAllocationType
{
	PHYSICS,
	AI,
	RENDERING,
	NODES,
};

enum EBlockType{

	FREE,
	USED,
};