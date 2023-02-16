#include "precompile-header/coreIncludes.h"
#include "MeshRenderer.h"
#include "graphics/rendering/Renderer.h"
#include "graphics/objects/Mesh.h"

#include "util/Transform.h"
#include "util/other/PollingStation.h"
#include "factories/MeshFactory.h"
#include "factories/ShaderFactory.h"


void drach::MeshRenderer::Start(InitializeContext& anInitContext)
{
	myPollingStation = &anInitContext.myPollingStation;
}

void drach::MeshRenderer::Update(RuntimeContext& aRuntimeContext)
{
	if (!myPollingStation) return;
	entt::registry& reg = aRuntimeContext.myRegistry;
	MeshFactory* meshFactory = myPollingStation->Get<MeshFactory>();
	ShaderFactory* shaderFactory = myPollingStation->Get<ShaderFactory>();
	Renderer* renderer = myPollingStation->Get<Renderer>();
	Transform& transform = reg.get<Transform>(myEntity);
	Shader shader = shaderFactory->GetShaderFromFile(myShaderName);

	renderer->Submit(*meshFactory->GetMesh(myMeshName), transform, shader);
}

void drach::MeshRenderer::LoadMesh(std::string_view aFilePath)
{
	if (!myPollingStation) return;
	myMeshName = aFilePath.data();
}
