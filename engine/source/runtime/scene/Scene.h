#pragma once
#include "componentSys/Entity.h"
#include "runtime/Context.h"
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
		ecs::Registry* myRegistry;
	};
}