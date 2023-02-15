#include "precompile-header/coreIncludes.h"
#include "Scene.h"
#include "componentSys/Registry.h"
#include "logging/Logger.h"
#include "util/other/MethodCheck.h"



drach::Scene::Scene()
{
	myRegistry.reset(new entt::registry());
}

void drach::Scene::Start(InitializeContext& const anInitContext)
{
	LOG("Start method called!");

	for (auto storage : myRegistry->storage())
	{
		for (auto entity : storage.second)
		{
			if (myStartCallbacks.count(entity))
			{
				myStartCallbacks[entity](anInitContext);
			}
		}
	}
	
}

void drach::Scene::Update(RuntimeContext& const aRuntimeContext)
{
	//LOG("Update method called! [Delta: " + std::to_string(aRuntimeContext.myDeltaTime) + "]");

	for (auto storage : myRegistry->storage())
	{
		for (auto entity : storage.second)
		{
			if (myUpdateCallbacks.count(entity))
			{
				myUpdateCallbacks[entity](aRuntimeContext);
			}
		}
	}
}

entt::entity drach::Scene::CreateEntity(Scene& aScene)
{
	return aScene.myRegistry->create();
}

void drach::Scene::DestroyEntity(Scene& aScene, entt::entity anEntity)
{
	aScene.myRegistry->destroy(anEntity);
}



template<typename Type, typename ...Args>
Type& drach::Scene::Emplace(Scene& aScene, entt::entity anEntity, Args ...someArgs)
{
	if constexpr (Has_Start<Type, void(InitializeContext&)>::value)
	{
		myStartCallbacks[anEntity] = std::bind(&Type::Start);
	}
	if constexpr (Has_Update<Type, void(RuntimeContext&)>::value)
	{
		myUpdateCallbacks[anEntity] = std::bind(&Type::Update);
	}
	return aScene.myRegistry->emplace<Type>(anEntity, someArgs...);
	// TODO: insert return statement here
}
template<typename Type>
Type& drach::Scene::Get(Scene& aScene, entt::entity anEntity)
{
	return aScene.myRegistry->get<Type>(anEntity);
}


