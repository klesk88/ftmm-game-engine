#ifndef __GameObject_H__
#define __GameObject_H__

#include "event.h"
#include <vector>

class GameObject{
public:
	virtual void update(std::vector<std::vector<Event*>>* ev);
};

#endif

