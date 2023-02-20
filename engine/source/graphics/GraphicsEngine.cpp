#include "precompile-header/coreIncludes.h"
#include "GraphicsEngine.h"
#include <cassert>

#include "logging/Logger.h"
#include "graphics/constant-buffers/BufferDef.h"
#define REPORT_DX_WARNINGS

namespace drach
{
	GraphicsEngine::GraphicsEngine() = default;
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

		UINT creationFlags = 0;
#if defined(REPORT_DX_WARNINGS)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		HRESULT result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, creationFlags, NULL, 0, D3D11_SDK_VERSION, &desc, &swapChain, &device, NULL, &deviceContext);

		assert(SUCCEEDED(result) && "Failed to create Swap Chain, Device and Device Context!");
		LOG("Successfully created Swap chain, Device and Device Context!");




	}

	void GraphicsEngine::DrawTo(drach::Vector4f aColor, RenderTarget* const aTarget, DepthStencil* const aDepthBuffer)
	{
		if (!aTarget->Get()) return;

		deviceContext->ClearRenderTargetView(aTarget->Get(), &aColor.x);
		if (aDepthBuffer)
			deviceContext->ClearDepthStencilView(aDepthBuffer->Get(), 0, 0, 1);
		if (aDepthBuffer)
			deviceContext->OMSetRenderTargets(1, aTarget->GetAddressOf(), aDepthBuffer->Get());
		else
			deviceContext->OMSetRenderTargets(1, aTarget->GetAddressOf(), nullptr);


		LOG("Switched Render Target!");
	}

	void GraphicsEngine::DrawToBackBuffer(drach::Vector4f aColor)
	{
		DrawTo(aColor, &backBuffer, &depthBuffer);
	}




	/* TODO: Try to create a full screen pass, then render the incoming "Shader Resource View" to the target "RenderTarget".
	*
	void GInterface::CopyRTtoRT(mys::RenderTarget& aDst, mys::RenderTarget& aSrc)
	{
		SetBlendState(mys::BlendState::Disabled);
		SetRenderTarget(aDst);
		PSSetResrouce(aSrc.GetShaderResource(), 0, 1);
		myFSEffect.Render(*this);
	}

	void GInterface::CopyRTtoBB(mys::RenderTarget& aSrc)
	{
		SetBlendState(mys::BlendState::Disabled);
		ChangeToMainFramebuffer(true, false);
		PSSetResrouce(aSrc.GetShaderResource(), 0, 1);
		myFSEffect.Render(*this);
	}


	*/


	void GraphicsEngine::CopyRenderToTargetBuffer(RenderResource* const aSource, RenderTarget* const aTarget)
	{
		//Switch to target renderTarget
		DrawTo({ 0,0,0,1 }, aTarget);
		//Bind the resource to the current drawing element
		deviceContext->PSSetShaderResources(0, 1, aSource->GetAddressOf());
		//Draw the final result
		deviceContext->DrawIndexed(3, 0, 0);
	}

	void GraphicsEngine::CopyRenderToBackBuffer(RenderResource* const aSource)
	{
		CopyRenderToTargetBuffer(aSource, &backBuffer);
	}

	void GraphicsEngine::Present()
	{
		swapChain->Present(0, 0);
	}
}

