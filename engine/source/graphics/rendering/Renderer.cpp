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
drach::Renderer::Renderer(PollingStation& aPollingStation) : myPollingStation(&aPollingStation)
{
}

void drach::Renderer::Render(Scene& const aScene, Transform& const aCamTransform)
{
	GraphicsEngine* gEngine = myPollingStation->Get<GraphicsEngine>();

	if (!gEngine)
	{
		LOG_ERROR("Missing Graphics Engine ptr in the polling station!");
		return;
	}

	//Set the graphics engine to draw to the current render target
	gEngine->DrawTo(&myRenderTarget, &myDepthBuffer);

	GDContext& context = gEngine->GetContext();
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	entt::registry& reg = aScene.GetRegistry();

	auto view = reg.view<Model, Transform>();

	for (auto [entity, model, transform] : view.each())
	{
		RenderModel(model, transform, context);
	}

	//Draw stuff
	gEngine->CopyRenderToBackBuffer(&myRenderData);
}


void drach::Renderer::RenderModel(const Model& aModel, const Transform& aTransform, const GDContext& aContext)
{
	auto shaderFactory = myPollingStation->Get<ShaderFactory>();

	for (size_t i = 0; i < aModel.GetSubMeshCount(); i++)
	{
		auto& mesh = aModel.GetSubMeshes()[i];
		//auto& mat = aModel.GetMaterials()[i];

		//InputLayout layout;
		///*if (!shaderFactory->GetInputLayout(mat.myInputLayout, layout))
		//{
		//	LOG_ERROR("Mesh " + mesh->myName + std::string(" with material ") + mat.myName + std::string(" missing an input layout!"));
		//	return;
		//}*/
		//aContext->IASetInputLayout(layout.Get());

		//unsigned int stride = sizeof(Vertex);
		//unsigned int offset = 0;

		//
		//aContext->IASetVertexBuffers(0, 1, mesh->myVertexBuffer.GetAddressOf(), &stride, &offset);
		//aContext->IASetIndexBuffer(mesh->myIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

		//VertexShader vertexShader;
		//PixelShader pixelShader;

		///*if (!shaderFactory->GetVertexShader(mat.myVertexShader, vertexShader))
		//{
		//	LOG_ERROR("Mesh " + mesh->myName + std::string(" with material ") + mat.myName + std::string(" missing a vertex shader!"));
		//	return;
		//}

		//if (!shaderFactory->GetPixelShader(mat.myPixelShader, pixelShader))
		//{
		//	LOG_ERROR("Mesh " + mesh->myName + std::string(" with material ") + mat.myName + std::string(" missing a vertex shader!"));
		//	return;
		//}*/

		//aContext->VSSetShader(vertexShader.Get(), nullptr, 0);
		//aContext->PSSetShader(pixelShader.Get(), nullptr, 0);

		//aContext->DrawIndexed(mesh->myIndicesAmm, 0, 0);
	}

}
