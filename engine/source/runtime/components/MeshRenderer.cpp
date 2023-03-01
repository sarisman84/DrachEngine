#include "precompile-header/coreIncludes.h"
#include "MeshRenderer.h"
#include "graphics/rendering/Renderer.h"
#include "graphics/objects/Mesh.h"

#include "util/Transform.h"
#include "util/other/PollingStation.h"
#include "factories/MeshFactory.h"
#include "factories/ShaderFactory.h"
#include "factories/TextureFactory.h"
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
	TextureFactory* textureFactory = myPollingStation->GetTextureFactory();
	Renderer* renderer = myPollingStation->GetRenderer();
	Transform& transform = reg.get<Transform>(myEntity);
	Shader shader = shaderFactory->GetShaderFromFile(myVertexShader, myPixelShader);
	if (!shader)
	{
		LOG_ERROR("Failed to submit instruction: Invalid shader!");
		return;
	}
	Texture texture = textureFactory->GetTexture(myTextureName);
	if (!texture)
	{
		LOG_ERROR("Failed to submit instruction: Invalid texture!");
		return;
	}
	renderer->Submit(*meshFactory->GetMesh(myMeshName), transform, shader, texture);
}

void drach::MeshRenderer::LoadMesh(std::string_view aFilePath)
{
	if (!myPollingStation) return;
	myMeshName = aFilePath.data();
}

void drach::MeshRenderer::LoadShader(const std::string_view& aShaderName)
{
	if (!myPollingStation) return;
	myVertexShader = aShaderName.data();
	myPixelShader = aShaderName.data();
}

void drach::MeshRenderer::LoadShader(const std::string_view& aVertexShader, const std::string_view& aPixelShader)
{
	if (!myPollingStation) return;
	myVertexShader = aVertexShader.data();
	myPixelShader = aPixelShader.data();
}

void drach::MeshRenderer::LoadTexture(std::string_view aTexturePath)
{
	if (!myPollingStation) return;
	myTextureName = aTexturePath.data();
}
