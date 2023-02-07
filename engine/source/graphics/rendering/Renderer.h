#pragma once
#include "graphics/DirectX11/DXTypes.h"

namespace drach
{
	class PollingStation;
	class GraphicsEngine;
	class Scene;
	class Model;
	struct Transform;


	class Renderer
	{
	public:
		Renderer(PollingStation& aGraphicsEngine);
	public:
		//Renders a scene containing entites with models. 
		void Render(Scene& const aScene, Transform& const aCamTransform);
	private:
		void RenderModel(const Model& aModel, const Transform& aTransform, const GraphicsDeviceContext& aContext);
	private:
		RenderTarget myRenderTarget;
		DepthStencil myDepthBuffer;
		RenderResource myRenderData;
		PollingStation* myPollingStation;
	};
}