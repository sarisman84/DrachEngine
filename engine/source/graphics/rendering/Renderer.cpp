#include "precompile-header/coreIncludes.h"
#include "Renderer.h"
#include "graphics/GraphicsEngine.h"
#include "runtime/scene/Scene.h"
#include "componentSys/Registry.h"

#include "logging/Logger.h"
#include "util/other/PollingStation.h"
#include "graphics/objects/Model.h"
#include "util/Transform.h"
#include "factories/ShaderFactory.h"
#include "entt/single_include/entt/entt.hpp"

#include "graphics/constant-buffers/BufferDef.h"
#include "graphics/constant-buffers/ConstantBuffer.h"

drach::Renderer::Renderer(PollingStation& aPollingStation) : myPollingStation(&aPollingStation)
{
	
	
}

void drach::Renderer::Init()
{
	GraphicsEngine& gEngine = *myPollingStation->Get<GraphicsEngine>();
	ConstantBuffer::Initialize<ObjectBuffer>(gEngine);
}

void drach::Renderer::Render(RenderContext& someContext)
{
	GraphicsEngine gEngine;
	ShaderFactory shaderFactory;

	ID3D11DeviceContext* context = gEngine.GetContext();

	if (!FetchManagers(gEngine, shaderFactory)) return;

	//Swap to the renderer's render target and depth buffer
	gEngine.DrawTo(&myRenderTarget, &myDepthBuffer);


	std::sort(myRenderInstructions.begin(), myRenderInstructions.end(),
		[](const std::unique_ptr<RenderInstruction>& a, const std::unique_ptr<RenderInstruction>& b)
		{
			return a->myShader.GetID() < b->myShader.GetID();
		});
	static StringID previousShader;
	for (auto& renderInstruction : myRenderInstructions)
	{
		Shader& shader = renderInstruction->myShader;

		if (previousShader != shader.GetID())
		{
			LOG("Binded new shader!");
			shader.Bind(gEngine);
			previousShader = shader.GetID();
		}

		Mesh& mesh = renderInstruction->myMesh;
		Transform& transform = renderInstruction->myTransform;
		mesh.Bind(gEngine);
		ObjectBuffer buffer(transform.GetMatrix());
		ConstantBuffer::Bind<ObjectBuffer, BindType::Vertex>(gEngine, buffer, 1);

		context->DrawIndexed(mesh.myIndicesAmm, 0, 0);


	}

	previousShader = StringID();

	gEngine.Present();
	myRenderInstructions.clear();
}

void drach::Renderer::Submit(Mesh& aModel, Transform& aTransform, Shader& aShader)
{
	RenderInstruction instruction(aModel, aTransform, aShader);
	myRenderInstructions.push_back(std::make_unique<RenderInstruction>(instruction));


}

const bool drach::Renderer::FetchManagers(GraphicsEngine& anEngine, ShaderFactory& aShaderFactory)
{

	GraphicsEngine* gEngine = myPollingStation->Get<GraphicsEngine>();

	if (!gEngine)
	{
		LOG_ERROR("Missing Graphics Engine ptr in the polling station!");
		return false;
	}

	ShaderFactory* shaderFactory = myPollingStation->Get<ShaderFactory>();

	if (!shaderFactory)
	{
		LOG_ERROR("Missing Shader Factory ptr in the polling station!");
		return false;
	}

	anEngine = *gEngine;
	aShaderFactory = *shaderFactory;
	return true;
}




