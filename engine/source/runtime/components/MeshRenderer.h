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
		MeshRenderer();
		MeshRenderer(PollingStation& aPollingStation, entt::entity anEntity);

		void Start(InitializeContext& anInitContext);
		void Update(RuntimeContext& aRuntimeContext);

		void LoadMesh(std::string_view aFilePath);
		void LoadShader(const std::string_view& aShaderName);
		void LoadShader(const std::string_view& aVertexShader, const std::string_view& aPixelShader);
		void LoadTexture(std::string_view aTexturePath);
	private:
		entt::entity myEntity;
		std::string myMeshName;
		std::string myVertexShader;
		std::string myPixelShader;
		std::string myTextureName;
		PollingStation* myPollingStation = nullptr;

	};
}