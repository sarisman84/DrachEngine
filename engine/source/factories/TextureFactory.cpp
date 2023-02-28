#include "precompile-header/coreIncludes.h"
#include "TextureFactory.h"
#include <xhash>


#include "logging/Logger.h"
#include "graphics/GraphicsEngine.h"

drach::TextureFactory::TextureFactory(GraphicsEngine& aGraphicsEngine)
{
}

drach::Texture drach::TextureFactory::GetTexture(const std::string_view& aFile)
{
	size_t key = std::hash<std::string_view>()(aFile);

	if (myTextures.count(key) > 0)
	{
		Texture result(*this, static_cast<uint32_t>(key));
		return result;
	}

	typedef std::filesystem::path filePath;

	filePath path(aFile);

	TextureInitContext context{ path.filename().string(), path, key };


	if (path.extension().compare("dds"))
	{
		return LoadDDS(context);
	}
	else if (path.extension().compare("png"))
	{
		return LoadPNG(context);
	}

	return Texture(*this, uint32_t(-1));
}


struct DDSInfo
{
	RenderResource myResource;
	uint32_t myWidth;
	uint32_t myHeight;
};



HRESULT CreateDDSTextureFromFile(DDSInfo& someInfo, drach::TextureInitContext& someData, drach::GraphicsEngine& anEngine)
{
	ID3D11Device* device = anEngine.GetDevice();

	RenderResource resource;

	HRESULT r = DirectX::CreateDDSTextureFromFile(device, someData.myFilePath.wstring().c_str(), nullptr, &resource);
	if (FAILED(r))
	{
		LOG_ERROR("Failed to load dds file from file: " + someData.myName);
		return r;
	}


	GTexture texture;
	resource->GetResource(reinterpret_cast<ID3D11Resource**>(texture.GetAddressOf()));
	D3D11_TEXTURE2D_DESC desc = {};
	texture->GetDesc(&desc);

	someInfo.myResource = resource;
	someInfo.myHeight = desc.Height;
	someInfo.myWidth = desc.Width;

	return S_OK;
}



drach::Texture drach::TextureFactory::LoadDDS(TextureInitContext& someData)
{

	ID3D11Device* device = myEngine->GetDevice();
	RenderResource resource;
	DDSInfo info;

	

	HRESULT r = CreateDDSTextureFromFile(info, someData, *myEngine);
	if (FAILED(r))
	{
		LOG_ERROR("Failed to load dds file from file: " + someData.myName);
		return Texture(*this, uint32_t(-1));
	}


	someData.myWidth = info.myWidth;
	someData.myHeight = info.myHeight;
	myTextures[someData.myID] = info.myResource;
	LOG("Loaded texture: " + someData.myName);
	return Texture(*this, someData.myID);
}

drach::Texture drach::TextureFactory::LoadPNG(TextureInitContext& someData)
{
	return Texture();
}

RenderResource drach::TextureFactory::ConstructShaderResource(const D3D11_TEXTURE2D_DESC& aDescription, TextureInitContext& someData)
{
	D3D11_SUBRESOURCE_DATA subRescData = {};
	subRescData.pSysMem = someData.myPixelData;
	subRescData.SysMemPitch = someData.myWidth * 4;
	subRescData.SysMemSlicePitch = someData.myWidth * someData.myHeight * 4;

	ID3D11Device* device = myEngine->GetDevice();
	GTexture texture;
	if (FAILED(device->CreateTexture2D(&aDescription, &subRescData, &texture)))
	{
		LOG_ERROR("Failed to create texture from " + someData.myName);
		return nullptr;
	}
	RenderResource resource;
	if (FAILED(device->CreateShaderResourceView(texture.Get(), NULL, &resource)))
	{
		LOG_ERROR("Failed to initialize shader resource view from " + someData.myName);
		return nullptr;
	}

	return resource;
}
