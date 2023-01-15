#pragma once
#include <iostream>

class TestComponent {
public:
	const char* name = "baseName";

	void printName() {
		std::cout << name << std::endl;
	}
};