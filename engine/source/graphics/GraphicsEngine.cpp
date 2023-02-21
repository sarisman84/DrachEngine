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



		ID3D11Texture2D* backBufferTexture;
		result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferTexture);
		if (FAILED(result))
		{
			return;
		}
		result = device->CreateRenderTargetView(backBufferTexture, nullptr, &backBuffer);
		if (FAILED(result))
		{
			return;
		}
		D3D11_TEXTURE2D_DESC textureDesc;
		backBufferTexture->GetDesc(&textureDesc);
		backBufferTexture->Release();



		ID3D11Texture2D* depthBufferTexture;
		D3D11_TEXTURE2D_DESC depthBufferDesc = { 0 };
		depthBufferDesc.Width = static_cast<unsigned int>(textureDesc.Width);
		depthBufferDesc.Height = static_cast<unsigned int>(textureDesc.Height);
		depthBufferDesc.ArraySize = 1;
		depthBufferDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		result = device->CreateTexture2D(&depthBufferDesc, nullptr, &depthBufferTexture);
		if (FAILED(result))
		{
			LOG_ERROR("Failed to create texture for depht buffer!");
			return;
		}
		result = device->CreateDepthStencilView(depthBufferTexture, nullptr, &depthBuffer);
		if (FAILED(result))
		{
			depthBufferTexture->Release();
			LOG_ERROR("Failed to create depth buffer!");
			return;
		}
		depthBufferTexture->Release();

		deviceContext->OMSetRenderTargets(1, backBuffer.GetAddressOf(), nullptr);
		D3D11_VIEWPORT viewport = { 0 };
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(textureDesc.Width);
		viewport.Height = static_cast<float>(textureDesc.Height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		deviceContext->RSSetViewports(1, &viewport);

	}

	void GraphicsEngine::DrawTo(drach::Vector4f aColor, RenderTarget& aTarget, DepthStencil& aDepthBuffer)
	{
		if (!aTarget.Get()) return;

		deviceContext->ClearRenderTargetView(aTarget.Get(), &aColor.x);
		if (aDepthBuffer)
			deviceContext->ClearDepthStencilView(aDepthBuffer.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		if (aDepthBuffer)
			deviceContext->OMSetRenderTargets(1, aTarget.GetAddressOf(), aDepthBuffer.Get());
		else
			deviceContext->OMSetRenderTargets(1, aTarget.GetAddressOf(), nullptr);


		/*LOG("Switched Render Target!");*/
	}

	void GraphicsEngine::DrawToBackBuffer(drach::Vector4f aColor)
	{
		DrawTo(aColor, backBuffer, depthBuffer);
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
		////Switch to target renderTarget
		//DrawTo({ 0,0,0,1 }, aTarget, depthBuffer);
		////Bind the resource to the current drawing element
		//deviceContext->PSSetShaderResources(0, 1, aSource->GetAddressOf());
		////Draw the final result
		//deviceContext->DrawIndexed(3, 0, 0);
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

