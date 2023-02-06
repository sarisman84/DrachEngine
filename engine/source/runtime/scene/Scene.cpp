#include "Scene.h"
#include "componentSys/Registry.h"
#include "logging/Logger.h"
drach::Scene::Scene()
{
	myRegistry.reset(new ecs::Registry());
}

void drach::Scene::Start(InitializeContext& const anInitContext)
{
	LOG("Start method called!");
	myRegistry->Start(anInitContext);
}

void drach::Scene::Update(RuntimeContext& const aRuntimeContext)
{
	LOG("Update method called! [Delta: " + std::to_string(aRuntimeContext.myDeltaTime) + "]");
	myRegistry->Update(aRuntimeContext);
}
