#include "MemoryManagement.h"

static const MemoryManagement* memory = MemoryManagement::getInstance();

static void* operator new(size_t size, EAllocationType inf){

		return MemoryManagement::operator new(size,inf);
}