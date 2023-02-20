#include "precompile-header/coreIncludes.h"
#include "Scene.h"
#include "componentSys/Registry.h"
#include "logging/Logger.h"
#include "util/other/MethodCheck.h"

#include "graphics/objects/camera/Camera.h"
#include "graphics/objects/camera/PerspectiveProjection.h"
#include "graphics/rendering/Renderer.h"

#include "util/Transform.h"
#include "util/other/PollingStation.h"

drach::Scene::Scene()
{
	myRegistry.reset(new entt::registry());
}

void drach::Scene::Start(PollingStation& aPollingStation)
{
	LOG("Start method called!");
	auto cameraEntity = myRegistry->create();
	Camera& cam = Scene::Emplace<Camera>(*this, cameraEntity, myRegistry.get(), cameraEntity, new Perspective(1920, 1080, 90));
	cam;

	Transform& transform = myRegistry->get<Transform>(cameraEntity);
	transform.position = { 0,0,-10 };

	myActiveCamera = cameraEntity;

	for (auto storage : myRegistry->storage())
	{
		for (auto entity : storage.second)
		{
			if (myStartCallbacks.count(entity))
			{
				InitializeContext initializeContext{ aPollingStation, entity };
				myStartCallbacks[entity](initializeContext);
			}
		}
	}

}

void drach::Scene::Update(PollingStation& aPollingStation, const float aDeltaTime)
{
	//LOG("Update method called! [Delta: " + std::to_string(aRuntimeContext.myDeltaTime) + "]");



	for (auto storage : myRegistry->storage())
	{
		for (auto entity : storage.second)
		{

			if (myUpdateCallbacks.count(entity))
			{
				RuntimeContext runtimeContext{ aPollingStation, entity, aDeltaTime, *myRegistry };
				myUpdateCallbacks[entity](runtimeContext);
			}
		}
	}
}

void drach::Scene::Render(Renderer& aRenderer)
{
	auto camera = GetActiveCamera(*this);

	RenderContext context{ std::get<Camera>(camera), std::get<Transform>(camera) };
	aRenderer.Render(context);

}

std::tuple<entt::entity, drach::Camera, drach::Transform> drach::Scene::GetActiveCamera(Scene& aScene)
{
	return std::make_tuple(aScene.myActiveCamera, Get <drach::Camera >(aScene, aScene.myActiveCamera), Get<drach::Transform>(aScene, aScene.myActiveCamera));
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


