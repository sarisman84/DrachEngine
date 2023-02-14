#pragma once
#include <d3d11.h>
#include <d3d11shader.h>
#include "DirectX11/DXTypes.h"


namespace drach
{
	class GraphicsEngine
	{
	public:
		GraphicsEngine();
		GraphicsEngine(HWND& const anWindowsInstance, const unsigned int aWidth, const unsigned int aHeight, const unsigned int aRefreshRate);
	public:
		void DrawTo(RenderTarget* const aTarget, DepthStencil* const aDepthBuffer = nullptr);
		void DrawToBackBuffer();
		void CopyRenderToTargetBuffer(RenderResource* const aSource, RenderTarget* const  aTarget);
		void CopyRenderToBackBuffer(RenderResource* const aTarget);
		void Present();

	public:
		inline GDevice& GetDevice() { return device; }
		inline GDContext& GetContext() { return deviceContext; }

	private:
		SwapChain swapChain;
		RenderTarget backBuffer;
		DepthStencil depthBuffer;
		GDevice device;
		GDContext deviceContext;
	};
}

