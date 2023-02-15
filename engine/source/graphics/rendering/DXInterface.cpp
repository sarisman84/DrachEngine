#include "precompile-header/coreIncludes.h"
#include "DXInterface.h"
#include "graphics/GraphicsEngine.h"

#define RETURN(result) \
if (someResult)		   \
* someResult = result; \
return *this

#define CHECKRESULT(result) if(FAILED(result))  \
{												\
 RETURN(result);								\
}

drach::dx11::RenderBuilder* drach::dx11::RenderBuilder::ourInstance;

drach::dx11::RenderBuilder::RenderBuilder(GDevice& aDevice) : myDevice(aDevice)
{
}

inline void drach::dx11::RenderBuilder::Init(GDevice& aDevice)
{
	ourInstance = new RenderBuilder(aDevice);
}

inline void drach::dx11::RenderBuilder::Release()
{
	if (ourInstance)
		delete ourInstance;
}

drach::dx11::RenderBuilder& drach::dx11::RenderBuilder::InitRenderTarget(RenderTarget& aRenderTargetToInit, D3D11_TEXTURE2D_DESC& aDesc, HRESULT* someResult)
{
	HRESULT foundResults;

	GTexture& texture = Data<GTexture>("renderTexture");
	foundResults = myDevice->CreateTexture2D(&aDesc, nullptr, &texture);
	CHECKRESULT(foundResults)
		foundResults = myDevice->CreateRenderTargetView(texture.Get(), nullptr, &aRenderTargetToInit);
	CHECKRESULT(foundResults)

		RETURN(foundResults);
}

drach::dx11::RenderBuilder& drach::dx11::RenderBuilder::InitRenderResource(RenderResource& aRenderResourceToInit, D3D11_TEXTURE2D_DESC* aDesc, HRESULT* someResult)
{
	HRESULT foundResults;

	GTexture texture = nullptr;
	if (aDesc)
	{
		foundResults = myDevice->CreateTexture2D(aDesc, nullptr, &texture);
		Data<GTexture>("renderTexture") = texture;
	}
	else
	{
		texture = Data<GTexture>("renderTexture");
	}


	CHECKRESULT(foundResults)
		foundResults = myDevice->CreateShaderResourceView(texture.Get(), nullptr, &aRenderResourceToInit);


	RETURN(foundResults);
}

drach::dx11::RenderBuilder& drach::dx11::RenderBuilder::InitDepthStencil(DepthStencil& aDepthStencilToInit, D3D11_DEPTH_STENCIL_VIEW_DESC& aDesc, HRESULT* someResult)
{
	HRESULT foundResults;
	GTexture& texture = Data<GTexture>("renderTexture");
	foundResults = myDevice->CreateDepthStencilView(texture.Get(), &aDesc, &aDepthStencilToInit);
	CHECKRESULT(foundResults)
		RETURN(foundResults);
}

HRESULT drach::dx11::BindResource(GDContext& aContext, RenderResource& aResource, const size_t aSlot, const size_t anAmount)
{
	return E_NOTIMPL;
}

HRESULT drach::dx11::BindConstantBuffer(GDContext& aContext, const BufferType aBufferTYype, GBuffer& aBuffer, const size_t aSlot, const size_t anAmount)
{
	return E_NOTIMPL;
}

void drach::dx11::SetViewport(GDContext& aContext, const PixelCoords& aSize, const PixelCoords& aStart, const uint32_t aMinDepth, const uint32_t aMaxDepth)
{
}

void drach::dx11::ClearDepthStencil(GDContext& aContext, DepthStencil& aStencil)
{
}

void drach::dx11::ClearRenderTarget(GDContext& aContext, RenderTarget& aTarget)
{
}
