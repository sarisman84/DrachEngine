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
#include "runtime/components/MeshRenderer.h"
#include "factories/MeshFactory.h"

drach::Scene::Scene()
{
}

drach::Scene::~Scene()
{
	delete[] mySystems.data();
	mySystems.clear();

}

void drach::Scene::Start(PollingStation& aPollingStation)
{
	LOG("Start method called!");
	CreateActiveCamera();

	for (auto& callback : mySystems)
	{
		callback->OnStart(myRegistry, aPollingStation);
	}

}

void drach::Scene::Update(PollingStation& aPollingStation, const float aDeltaTime)
{
	static float t = 0.0f;
	if (aDeltaTime > 0.0f)
		t += aDeltaTime;

	
	//LOG("Update method called! [Delta: " + std::to_string(cubeTransform.position.z) + "]");

	for (auto& callback : mySystems)
	{
		callback->OnUpdate(myRegistry, aPollingStation, aDeltaTime);
	}


	while (!myGarbageCollection.empty())
	{
		myRegistry.destroy(myGarbageCollection.front());
		myGarbageCollection.pop();
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
	return aScene.myRegistry.create();
}

void drach::Scene::DestroyEntity(Scene& aScene, entt::entity anEntity)
{
	aScene.myRegistry.destroy(anEntity);
}

void drach::Scene::Destroy(Scene& aScene, entt::entity anEntityToDelete)
{
	aScene.myGarbageCollection.push(anEntityToDelete);
}

void drach::Scene::CreateActiveCamera()
{
	auto cameraEntity = myRegistry.create();
	Camera& cam = Scene::Emplace<Camera>(*this, cameraEntity, &myRegistry, cameraEntity, new Perspective(1920, 1080, 90));
	cam;

	Transform& transform = myRegistry.get<Transform>(cameraEntity);
	transform.position = { 0,0,0.0f };
	transform.size = { 1.0f,1.0f,1.0f };
	transform.rotation = { 0.0f,0.0f,0.0f };

	myActiveCamera = cameraEntity;
}



template<typename Type, typename ...Args>
Type& drach::Scene::Emplace(Scene& aScene, entt::entity anEntity, Args ...someArgs)
{
	static bool isRegistered = false;
	Type& t = aScene.myRegistry.emplace<Type>(anEntity, someArgs...);
	if (!isRegistered)
	{
		isRegistered = true;
		aScene.mySystems.push_back(new RuntimeSystem<Type>());
	}

	return t;
}
template<typename Type>
Type& drach::Scene::Get(Scene& aScene, entt::entity anEntity)
{
	return aScene.myRegistry.get<Type>(anEntity);
}


