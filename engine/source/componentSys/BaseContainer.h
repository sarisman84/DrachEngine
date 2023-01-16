#pragma once
#include "Entity.h"

class BaseContainer {
public:
	unsigned long id;
	BaseContainer(unsigned long id) : id(id) {}

	static unsigned long GenerateID(unsigned long& id);


	virtual void Remove(const Entity entity) = 0;
};