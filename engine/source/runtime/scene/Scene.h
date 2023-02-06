#pragma once
#include "componentSys/Entity.h"
#include "runtime/Context.h"
#include <memory>
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
		inline ecs::Registry& GetRegistry() { return *myRegistry; }
	private:
		std::unique_ptr<ecs::Registry> myRegistry;
	};
}