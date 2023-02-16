#pragma once
#include "entt/single_include/entt/entt.hpp"
namespace drach
{
	class Scene;
	class PollingStation;


	struct InitializeContext
	{
		PollingStation& myPollingStation;
		entt::entity myEnttity;
	};


	struct RuntimeContext : public InitializeContext
	{
		float myDeltaTime;
		entt::registry& myRegistry;
	};

	//TODO: Add more data on each context (as well as unique variables per context) - Spyro
}