#pragma once
#include "graphics/DirectX11/DXTypes.h"

namespace drach
{
	class GraphicsEngine;
	class Scene;
	class Shader;
	struct Transform;


	class Renderer
	{
	public:
		Renderer(GraphicsEngine& aGraphicsEngine);
	public:
		//Renders a scene containing entites with models. 
		void Render(Scene& const aScene, Transform& const aTransform, Shader& const aShader);
	private:
		RenderTarget myRenderTarget;
		DepthStencil myDepthBuffer;
		RenderResource myRenderData;
		GraphicsEngine& myGraphicsEngine;
	};
}