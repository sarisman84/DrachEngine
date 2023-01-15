#pragma once
#include "DirectX11/DXTypes.h"
class GraphicsEngine 
{
public:
	GraphicsEngine(HWND& const anWindowsInstance, const unsigned int aWidth, const unsigned int aHeight, const unsigned int aRefreshRate);
public:
	void DrawTo(RenderTarget* const aTarget, DepthStencil* const aDepthBuffer = nullptr);
	void DrawToBackBuffer();
	void Present();
private:
	SwapChain swapChain;
	RenderTarget backBuffer;
	DepthStencil depthBuffer;
	GraphicsDevice device;
	GraphicsDeviceContext deviceContext;
};