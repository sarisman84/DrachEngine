#include "main.h"
#include <iostream>
#include <d3d11.h>

#include "componentSys/Registry.h"
#include "componentSys/TestComponent.h"

void Engine::OnUpdate()
{
	
}

void Engine::OnStart(StartContext& const someData)
{
	myGraphicsEngine.reset(new GraphicsEngine(someData.myWindowsInstance, someData.myWindowWidth, someData.myWindowHeight, 120));


	//TESTING THE REGISTRY
	std::cout << "START" << std::endl;

	Registry reg = Registry();
	//TODO: make entities in the registry
	Entity A = 0;
	Entity B = 2;
	reg.Add<float>(A);
	reg.Add<TestComponent>(A)->name = "As comp";
	reg.Add<TestComponent>(B)->name = "Bs comp";

	reg.Get<TestComponent>(A)->printName();
	reg.Get<TestComponent>(B)->printName();
}

void Engine::OnWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
}

extern "C"
{
	_declspec(dllexport) EngineInterface* ExportInterface()
	{
		return new Engine();
	}
}