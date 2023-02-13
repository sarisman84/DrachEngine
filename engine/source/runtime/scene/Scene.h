#pragma once
#define NOMINMAX

#include "componentSys/Entity.h"
#include "runtime/Context.h"
#include <memory>
#include <tuple>
#include <functional>


#include "entt/single_include/entt/entt.hpp"



FORWARD_DECLARE_REG


namespace drach
{
	class Scene
	{
	public:
		Scene();
		void Start(InitializeContext& const anInitContext);
		void Update(RuntimeContext& const aRuntimeContext);
	public:

		static entt::entity CreateEntity(Scene& aScene);
		static void DestroyEntity(Scene& aScene, entt::entity anEntity);


		template<typename Type, typename... Args>
		static Type& Emplace(Scene& aScene, entt::entity anEntity, Args... someArgs);

		template<typename Type>
		static Type& Get(Scene& aScene, entt::entity anEntity);



		inline entt::registry& GetRegistry() { return *myRegistry; }
	private:
		std::unordered_map<entt::entity, std::function<void(InitializeContext&)>> myStartCallbacks;
		std::unordered_map<entt::entity, std::function<void(RuntimeContext&)>> myUpdateCallbacks;
	private:
		//std::unique_ptr<ecs::Registry> myRegistry;
		std::unique_ptr<entt::registry> myRegistry;
	};

}