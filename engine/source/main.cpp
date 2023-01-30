#include "main.h"

#include "logging/Logger.h"
#include <string>
#include <typeinfo>

#include "componentSys/Registry.h"
#include "componentSys/TestComponent.h"
#include "util/Transform.h"

#include "util/other/SMap.h"

#include "graphics/GraphicsEngine.h"
void Engine::OnUpdate()
{
	
}

void Engine::OnStart(StartContext& const someData)
{
	using namespace drach::ecs;
	myGraphicsEngine.reset(new drach::GraphicsEngine(someData.myWindowsInstance, someData.myWindowWidth, someData.myWindowHeight, 120));
	LOG("Engine Initialized!");


	//TESTING THE REGISTRY

	Registry reg = Registry();

	Entity A = reg.CreateEntity();
	Entity B = reg.CreateEntity();
	reg.Add<float>(A);
	drach::Transform& transform = reg.Add<drach::Transform>(A);
	reg.Add<TestComponent>(A).name = "As comp";
	reg.Add<TestComponent>(B).name = "Bs comp";

	transform.position = { 10, 0, 10 };



	reg.Get<TestComponent>(A)->printName();
	reg.Get<TestComponent>(B)->printName();


	drach::Transform* newTransform = reg.Get<drach::Transform>(A);
	std::cout << "Pos:(" << newTransform->position.x << ", " << newTransform->position.y << ", " << newTransform->position.z << ")\n";
	reg.DestroyEntity(A);
	std::cout << reg.Get<TestComponent>(A) << std::endl;
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