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
	auto cameraEntity = myRegistry.create();
	Camera& cam = Scene::Emplace<Camera>(*this, cameraEntity, &myRegistry, cameraEntity, new Perspective(1920, 1080, 90));
	cam;

	Transform& transform = myRegistry.get<Transform>(cameraEntity);
	transform.position = { 0,0,0.0f };
	transform.size = { 1.0f,1.0f,1.0f };
	transform.rotation = { 0.0f,0.0f,0.0f };

	myActiveCamera = cameraEntity;



	auto testCube = myRegistry.create();
	myTestCube = testCube;

	Transform& cubeTransform = Scene::Emplace<Transform>(*this, testCube, &myRegistry, testCube);
	cubeTransform.position = { 0,0,1.25f };
	cubeTransform.size = { 1,1,1 };
	cubeTransform.rotation = { 0,0,0 };

	MeshRenderer& cubeMesh = Scene::Emplace<MeshRenderer>(*this, testCube, aPollingStation, testCube);

	cubeMesh.LoadMesh("resources/meshes/icosphere.fbx");
	cubeMesh.LoadShader("Cube");

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

	Transform& cubeTransform = Scene::Get<Transform>(*this, myTestCube);
	cubeTransform.position.z = std::sinf(t);
	//LOG("Update method called! [Delta: " + std::to_string(cubeTransform.position.z) + "]");

	static std::vector<BaseSystem*> cpy;
	cpy = mySystems;

	for (auto& callback : cpy)
	{
		callback->OnUpdate(myRegistry, aPollingStation, aDeltaTime);
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


