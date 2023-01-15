#include "GraphicsEngine.h"
#include <d3d11.h>
#include <cassert>
#pragma comment(lib, "d3d11.lib")

GraphicsEngine::GraphicsEngine(HWND& const anWindowsInstance, const unsigned int aWidth, const unsigned int aHeight, const unsigned int aRefreshRate)
{
	DXGI_SWAP_CHAIN_DESC desc = {};
	desc.BufferDesc.Width = aWidth;
	desc.BufferDesc.Height = aHeight;
	desc.BufferDesc.RefreshRate.Numerator = aRefreshRate;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 1;
	desc.Windowed = true;
	desc.OutputWindow = anWindowsInstance;
	desc.Flags = 0;

	HRESULT result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &desc, &swapChain, &device, NULL, &deviceContext);

	assert(result == S_OK && "Failed to create Swap Chain, Device and Device Context!");
}

void GraphicsEngine::DrawTo(RenderTarget* const aTarget, DepthStencil* const aDepthBuffer)
{
	if (aDepthBuffer)
		deviceContext->OMSetRenderTargets(1, aTarget->GetAddressOf(), aDepthBuffer->Get());
	else
		deviceContext->OMSetRenderTargets(1, aTarget->GetAddressOf(), nullptr);
}

void GraphicsEngine::DrawToBackBuffer()
{
	DrawTo(&backBuffer, &depthBuffer);
}

void GraphicsEngine::Present()
{
	swapChain->Present(0, 0);
}
