#pragma once

class BaseContainer {
public:
	unsigned long id;
	BaseContainer(unsigned long id) : id(id) {}


	static unsigned long GenerateID(unsigned long& id);
};