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
	myTextureFactory = myPollingStation->GetTextureFactory();

	myBufferManager = ConstantBuffer(*myGraphicsEngine);
	ConstantBuffer::Initialize<ObjectBuffer>(myBufferManager);
	ConstantBuffer::Initialize<FrameBuffer>(myBufferManager);

}

void drach::Renderer::Render(RenderContext& someContext)
{
	if (!myGraphicsEngine) return;
	ID3D11DeviceContext* context = myGraphicsEngine->GetContext();
	//Swap to the renderer's render target and depth buffer
	myGraphicsEngine->DrawToBackBuffer({ 0.25f,0.25f,0.5f,1 });
	FrameBuffer fBuffer(someContext.myCamera.ViewMatrix());
	ConstantBuffer::Bind<FrameBuffer, BindType::Vertex>(myBufferManager, fBuffer, 0);

	std::sort(myRenderInstructions.begin(), myRenderInstructions.end(),
		[](RenderInstruction& a, RenderInstruction& b)
		{
			return a.myShader.GetID() < b.myShader.GetID();
		});

	static StringID previousShader;
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	for (auto& renderInstruction : myRenderInstructions)
	{
		Shader& shader = renderInstruction.myShader;
		Mesh& mesh = renderInstruction.myMesh;
		Texture& texture = renderInstruction.myTexture;

		mesh.Bind(*myGraphicsEngine);

		if (previousShader != shader.GetID())
		{
			shader.Bind(*myGraphicsEngine, *myShaderFactory);
			previousShader = shader.GetID();
		}

		if (texture)
			texture.Bind(*myGraphicsEngine, *myTextureFactory, 0);

		Transform& transform = renderInstruction.myTransform;

		ObjectBuffer oBuffer(transform.GetMatrix(true));
		ConstantBuffer::Bind<ObjectBuffer, BindType::Vertex>(myBufferManager, oBuffer, 1);

		context->DrawIndexed(mesh.myIndicesAmm, 0, 0);


	}


	myGraphicsEngine->Present();
	
}

void drach::Renderer::EndFrame()
{
	myRenderInstructions.clear();
}

void drach::Renderer::Submit(Mesh& aModel, Transform& aTransform, Shader& aShader, Texture& aTexture)
{
	RenderInstruction instruction(aModel, aTransform, aShader, aTexture);
	myRenderInstructions.push_back(instruction);


}






