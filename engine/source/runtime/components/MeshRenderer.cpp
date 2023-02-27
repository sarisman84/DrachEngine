#include "precompile-header/coreIncludes.h"
#include "MeshRenderer.h"
#include "graphics/rendering/Renderer.h"
#include "graphics/objects/Mesh.h"

#include "util/Transform.h"
#include "util/other/PollingStation.h"
#include "factories/MeshFactory.h"
#include "factories/ShaderFactory.h"
#include "logging/Logger.h"

drach::MeshRenderer::MeshRenderer() = default;

drach::MeshRenderer::MeshRenderer(PollingStation& aPollingStation, entt::entity anEntity)
	:myPollingStation(&aPollingStation), myEntity(anEntity)
{
}

void drach::MeshRenderer::Start(InitializeContext& anInitContext)
{
	myPollingStation = &anInitContext.myPollingStation;
}

void drach::MeshRenderer::Update(RuntimeContext& aRuntimeContext)
{
	myPollingStation = &aRuntimeContext.myPollingStation;

	

	entt::registry& reg = aRuntimeContext.myRegistry;
	MeshFactory* meshFactory = myPollingStation->GetMeshFactory();
	ShaderFactory* shaderFactory = myPollingStation->GetShaderFactory();
	Renderer* renderer = myPollingStation->GetRenderer();
	Transform& transform = reg.get<Transform>(myEntity);
	Shader shader = shaderFactory->GetShaderFromFile(myShaderName);
	if (shader.GetID() == StringID())
	{
		LOG_ERROR("Failed to submit instruction: Invalid shader!");
		return;
	}
	renderer->Submit(*meshFactory->GetMesh(myMeshName), transform, shader);
}

void drach::MeshRenderer::LoadMesh(std::string_view aFilePath)
{
	if (!myPollingStation) return;
	myMeshName = aFilePath.data();
}

void drach::MeshRenderer::LoadShader(std::string_view aShaderName)
{
	if (!myPollingStation) return;
	myShaderName = aShaderName.data();
}
