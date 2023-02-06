#pragma once
namespace drach
{
	class Scene;
	class PollingStation;


	struct InitializeContext
	{
		PollingStation& myPollingStation;
	};


	struct RuntimeContext : public InitializeContext
	{
		float myDeltaTime;
	};

	//TODO: Add more data on each context (as well as unique variables per context) - Spyro
}