#pragma once
#include <windows.h>
#include <map>
#include"SegmentInformation.h"
//#include "EAllocationType.h"

using namespace std;


class FreeMemory{
public:
	map<unsigned long,SegmentInformation*> free_memory_heap;

};

