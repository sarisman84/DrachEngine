#pragma once
#define NOMINMAX
#include <vector>
#include <tuple>
#include <memory>
#include "graphics/DirectX11/DXTypes.h"
#include "graphics/constant-buffers/ConstantBuffer.h"
#include "util/Transform.h"
#include "graphics/objects/Mesh.h"
#include "factories/ShaderFactory.h"

namespace drach
{
	class Camera;
	class PollingStation;
	class GraphicsEngine;
	class Scene;
	class Model;






	struct RenderContext
	{
		Camera& myCamera;
		Transform& myCameraTransform;
	};


	struct RenderInstruction
	{
		Mesh myMesh;
		Transform myTransform;
		Shader myShader;
	};

	class Renderer
	{
	public:
		Renderer(PollingStation& aStation);
	public:
		void Init();
		//Renders a scene containing entites with models. 
		void Render(RenderContext& someContext);
		void Submit(Mesh& aMesh, Transform& aTransform, Shader& aShader);
	private:
		const bool FetchManagers(GraphicsEngine*& anEngine, ShaderFactory*& aShaderFactory);
	private:
		std::vector<RenderInstruction> myRenderInstructions;
	private:
		ShaderFactory* myShaderFactory;
		GraphicsEngine* myGraphicsEngine;
		ConstantBuffer myBufferManager;
		RenderTarget myRenderTarget;
		DepthStencil myDepthBuffer;
		RenderResource myRenderData;
		PollingStation* myPollingStation;
	};
}