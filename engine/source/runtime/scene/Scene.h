#pragma once
#define NOMINMAX

#include "componentSys/Entity.h"
#include "runtime/Context.h"
#include <memory>
#include <tuple>
#include <functional>


#include "entt/single_include/entt/entt.hpp"




typedef std::tuple <entt::entity, std::function<void(drach::InitializeContext&)>> InitializeCallback;
typedef std::tuple <entt::entity, std::function<void(drach::RuntimeContext&)>> RuntimeCallback;

namespace drach
{
	class BaseSystem
	{
	public:
		BaseSystem() = default;
		virtual ~BaseSystem() = default;

		virtual void OnStart(entt::registry& aRegistry, PollingStation& aPollingStation) = 0;
		virtual void OnUpdate(entt::registry& aRegistry, PollingStation& aPollingStation, const float aDeltaTime) = 0;
	};


	template<typename Type>
	class RuntimeSystem : public BaseSystem
	{
	public:
		void OnStart(entt::registry& aRegistry, PollingStation& aPollingStation) override
		{
			if constexpr (Has_Start<Type, void(InitializeContext&)>::value)
			{
				auto view = aRegistry.view<Type>();
				for (auto [entity, type] : view.each())
				{
					drach::InitializeContext context{ aPollingStation, entity };
					type.Start(context);
				}
			}
		}
		void OnUpdate(entt::registry& aRegistry, PollingStation& aPollingStation, const float aDeltaTime) override
		{
			if constexpr (Has_Update<Type, void(RuntimeContext&)>::value)
			{
				auto view = aRegistry.view<Type>();
				for (auto [entity, type] : view.each())
				{
					drach::RuntimeContext context{ aPollingStation, entity,  aDeltaTime,aRegistry };
					type.Update(context);
				}
			}


		}
	};



	class Renderer;
	class Transform;
	class Camera;
	class PollingStation;
	class Scene
	{
	public:
		Scene();
		~Scene();

		void Start(PollingStation& aPollingStation);
		void Update(PollingStation& aPollingStation, const float aDeltaTime);
		void Render(Renderer& aRenderer);

	public:
		static std::tuple<entt::entity, drach::Camera, drach::Transform> GetActiveCamera(Scene& aScene);

		static entt::entity CreateEntity(Scene& aScene);
		static void DestroyEntity(Scene& aScene, entt::entity anEntity);


		template<typename Type, typename... Args>
		static Type& Emplace(Scene& aScene, entt::entity anEntity, Args... someArgs);

		template<typename Type>
		static Type& Get(Scene& aScene, entt::entity anEntity);
		inline entt::registry& GetRegistry() { return myRegistry; }
	private:
		std::vector<BaseSystem*> mySystems;
	private:
		//std::unique_ptr<ecs::Registry> myRegistry;
		entt::registry myRegistry;
		entt::entity myActiveCamera = entt::entity(-1);

	private:
		entt::entity myTestCube = entt::entity(-1);
	};


}