#pragma once
#define NOMINMAX
#include <vector>
#include <tuple>
#include <memory>
#include "graphics/DirectX11/DXTypes.h"

namespace drach
{
	class Camera;
	class PollingStation;
	class GraphicsEngine;
	class ShaderFactory;
	class Scene;
	class Model;
	class Mesh;
	struct Shader;
	struct Transform;




	struct RenderContext
	{
		Camera& myCamera;
		Transform& myCameraTransform;
	};


	struct RenderInstruction
	{
		Mesh& myMesh;
		Transform& myTransform;
		Shader& myShader;
	};

	class Renderer
	{
	public:
		Renderer(PollingStation& aGraphicsEngine);
	public:
		//Renders a scene containing entites with models. 
		void Render(RenderContext& someContext);
		void Submit(Mesh& aMesh, Transform& aTransform, Shader& aShader);
	private:
		const bool FetchManagers(GraphicsEngine& anEngine, ShaderFactory& aShaderFactory);
	private:
		std::vector<std::unique_ptr<RenderInstruction>> myRenderInstructions;
	private:


		RenderTarget myRenderTarget;
		DepthStencil myDepthBuffer;
		RenderResource myRenderData;
		PollingStation* myPollingStation;
	};
}