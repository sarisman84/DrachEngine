#include "precompile-header/coreIncludes.h"
#include "main.h"

#include "logging/Logger.h"
#include <string>
#include <typeinfo>

#include "componentSys/Registry.h"
#include "componentSys/TestComponent.h"
#include "util/Transform.h"

#include "util/other/SMap.h"

#include "graphics/GraphicsEngine.h"
#include "factories/ShaderFactory.h"
#include "factories/MeshFactory.h"
#include "factories/TextureFactory.h"
#include "util/other/PollingStation.h"
#include "runtime/Context.h"
#include "runtime/scene/Scene.h"
#include "graphics/rendering/Renderer.h"
#include "util/Transform.h"






bool Engine::OnUpdate(RuntimeContext& someContext)
{
	myRenderer->EndFrame();

	if (myEditorInterface)
	{
		EditorRuntimeContext context{someContext.myDeltaTime, *this};
		myEditorInterface->OnUpdate(context);
	}
	else
	{
		myTestScene->Update(*myPollingStation, someContext.myDeltaTime);
	}

	myTestScene->Render(*myRenderer);
	return true;
}

#define _DEBUG
//Moved the ecs test stuff onto its own global method - Spyro
void TestECS()
{
	using namespace drach::ecs;
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
	/*std::cout << "Pos:(" << newTransform->position.x << ", " << newTransform->position.y << ", " << newTransform->position.z << ")\n";*/
	reg.DestroyEntity(A);
	std::cout << reg.Get<TestComponent>(A) << std::endl;
}

bool Engine::OnStart(StartContext& someData, EditorInterface* anEditorAPI)
{
	myEditorInterface = anEditorAPI;
	InitConsole();

	myPollingStation.reset(new drach::PollingStation());


	myGraphicsEngine = std::make_shared<drach::GraphicsEngine>(someData.myWindowsInstance, someData.myWindowWidth, someData.myWindowHeight, 120);
	myShaderFactory = std::make_shared<drach::ShaderFactory>(*myGraphicsEngine);
	myMeshFactory = std::make_shared<drach::MeshFactory>(*myGraphicsEngine);
	myTextureFactory = std::make_shared<drach::TextureFactory>(*myGraphicsEngine);
	myRenderer = std::make_shared<drach::Renderer>(*myPollingStation);




	myPollingStation->myGraphicsEnginePtr = myGraphicsEngine.get();
	LOG("PollingStation -> Registered Graphics Engine");
	myPollingStation->myShaderFactoryPtr = myShaderFactory.get();
	LOG("PollingStation -> Registered Shader Factory");
	myPollingStation->myMeshFactoryPtr = myMeshFactory.get();
	LOG("PollingStation -> Registered Mesh Factory");
	myPollingStation->myTextureFactory = myTextureFactory.get();
	LOG("PollingStation -> Registered Texture Factory");
	myPollingStation->myRendererPtr = myRenderer.get();
	LOG("PollingStation -> Registered Renderer");



	LOG("Engine Initialized!");


	myRenderer->Init();
	myTestScene = std::make_shared<drach::Scene>();



	if (myEditorInterface)
	{
		EditorContext context{ someData.myWindowsInstance, someData.myWindowWidth, someData.myWindowHeight, myGraphicsEngine->GetDevice(), myGraphicsEngine->GetContext() };

		myEditorInterface->OnStart(context);

		LOG("Editor found!");
	}

	myTestScene->Start(*myPollingStation);

	//TestECS();
	return true;

}

void Engine::OnWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void Engine::InitConsole()
{
#ifdef _DEBUG
	AllocConsole();

	FILE* newstdin = nullptr;
	FILE* newstdout = nullptr;
	FILE* newstderr = nullptr;

	freopen_s(&newstdin, "CONIN$", "r", stdin);
	freopen_s(&newstdout, "CONOUT$", "w", stdout);
	freopen_s(&newstderr, "CONOUT$", "w", stderr);
#endif
}

extern "C"
{
	_declspec(dllexport) EngineInterface* ExportInterface()
	{
		return new Engine();
	}
}