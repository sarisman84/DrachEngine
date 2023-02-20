#include "precompile-header/coreIncludes.h"
#include "Renderer.h"
#include "graphics/GraphicsEngine.h"
#include "runtime/scene/Scene.h"
#include "componentSys/Registry.h"

#include "logging/Logger.h"
#include "util/other/PollingStation.h"
#include "graphics/objects/Model.h"
#include "graphics/objects/camera/Camera.h"
#include "util/Transform.h"
#include "factories/ShaderFactory.h"
#include "entt/single_include/entt/entt.hpp"

#include "graphics/constant-buffers/BufferDef.h"


drach::Renderer::Renderer(PollingStation& aStation) :
	myPollingStation(&aStation)
{


}

void drach::Renderer::Init()
{
	myGraphicsEngine = myPollingStation->GetGraphicsEngine();
	myShaderFactory = myPollingStation->GetShaderFactory();

	myBufferManager = ConstantBuffer(*myGraphicsEngine);
	ConstantBuffer::Initialize<ObjectBuffer>(myBufferManager);
	ConstantBuffer::Initialize<FrameBuffer>(myBufferManager);

}

void drach::Renderer::Render(RenderContext& someContext)
{
	if (!myGraphicsEngine) return;
	ID3D11DeviceContext* context = myGraphicsEngine->GetContext();
	//Swap to the renderer's render target and depth buffer
	myGraphicsEngine->DrawTo({ 1,0,0,1 }, &myRenderTarget, &myDepthBuffer);
	FrameBuffer fBuffer(someContext.myCamera.ViewMatrix());
	ConstantBuffer::Bind<FrameBuffer, BindType::Vertex>(myBufferManager, fBuffer, 1);
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
			shader.Bind(*myGraphicsEngine);
			previousShader = shader.GetID();
		}

		Mesh& mesh = renderInstruction->myMesh;
		Transform& transform = renderInstruction->myTransform;
		mesh.Bind(*myGraphicsEngine);
		ObjectBuffer oBuffer(transform.GetMatrix());
		ConstantBuffer::Bind<ObjectBuffer, BindType::Vertex>(myBufferManager, oBuffer, 1);

		context->DrawIndexed(mesh.myIndicesAmm, 0, 0);


	}

	previousShader = StringID();

	myGraphicsEngine->Present();
	myRenderInstructions.clear();
}

void drach::Renderer::Submit(Mesh& aModel, Transform& aTransform, Shader& aShader)
{
	RenderInstruction instruction(aModel, aTransform, aShader);
	myRenderInstructions.push_back(std::make_unique<RenderInstruction>(instruction));


}

const bool drach::Renderer::FetchManagers(GraphicsEngine*& anEngine, ShaderFactory*& aShaderFactory)
{
	return true;
}




