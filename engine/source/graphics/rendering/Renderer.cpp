#include "Renderer.h"
#include "graphics/GraphicsEngine.h"

drach::Renderer::Renderer(GraphicsEngine& aGraphicsEngine) : myGraphicsEngine(aGraphicsEngine)
{
}

void drach::Renderer::Render(Scene& const aScene, Transform& const aTransform, Shader& const aShader)
{
	//Set the graphics engine to draw to the current render target
	myGraphicsEngine.DrawTo(&myRenderTarget, &myDepthBuffer);


	//Draw stuff
	myGraphicsEngine.CopyRenderToBackBuffer(&myRenderData);
}
