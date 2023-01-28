#include "main.h"

#include "logging/Logger.h"
#include <string>
#include <typeinfo>

#include "componentSys/Registry.h"
#include "componentSys/TestComponent.h"

#include "graphics/GraphicsEngine.h"
void Engine::OnUpdate()
{
	
}

void Engine::OnStart(StartContext& const someData)
{
	myGraphicsEngine.reset(new drach::GraphicsEngine(someData.myWindowsInstance, someData.myWindowWidth, someData.myWindowHeight, 120));
	LOG("Engine Initialized!");


	//TESTING THE REGISTRY

	Registry reg = Registry();

	Entity A = reg.CreateEntity();
	Entity B = reg.CreateEntity();
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