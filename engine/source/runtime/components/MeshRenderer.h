#pragma once
#include "entt/single_include/entt/entt.hpp"
#include "runtime/Context.h"
#include <string>
#include <memory>
namespace drach
{
	class PollingStation;
	class Mesh;
	class MeshRenderer
	{
	public:
		void Start(InitializeContext& anInitContext);
		void Update(RuntimeContext& aRuntimeContext);

		void LoadMesh(std::string_view aFilePath);

	private:
		entt::entity myEntity;
		std::string myMeshName;
		std::string myShaderName;
		PollingStation* myPollingStation = nullptr;

	};
}