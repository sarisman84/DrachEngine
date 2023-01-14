#include "main.h"
#include <iostream>
void Engine::OnStart()
{
	std::cout << "This is a test :) \n";
}

void Engine::OnUpdate()
{
}



extern "C"
{
	_declspec(dllexport) EngineInterface* ExportInterface()
	{
		return new Engine();
	}
}