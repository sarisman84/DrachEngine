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

drach::dx11::RenderBuilder::RenderBuilder(GraphicsDevice& aDevice) : myDevice(aDevice)
{
}

inline void drach::dx11::RenderBuilder::Init(GraphicsDevice& aDevice)
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


