#include "precompile-header/coreIncludes.h"
#include "TextureFactory.h"

#include <xhash>
#include "logging/Logger.h"
#include "graphics/GraphicsEngine.h"
#include "graphics/objects/Texture.h"
#include "DirectXTex/DDSTextureLoader/DDSTextureLoader11.cpp"

drach::TextureFactory::TextureFactory(GraphicsEngine& aGraphicsEngine)
	:myEngine(&aGraphicsEngine)
{
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	AddSamplerState(SAMPLER_DEFAULT_WRAP, samplerDesc);
}

drach::Texture drach::TextureFactory::GetTexture(const std::string_view& aFile, const std::string_view& aSamplerName)
{
	StringID key(aFile.data());
	StringID samplerKey(aSamplerName.data());

	if (myTextures.count(key) > 0)
	{
		Texture result(*this, key, samplerKey);
		return result;
	}

	typedef std::filesystem::path filePath;

	filePath path(aFile);

	TextureInitContext context{ path.filename().string(), path, key, samplerKey };


	if (path.extension().compare("dds"))
	{
		return LoadDDS(context);
	}
	else if (path.extension().compare("png"))
	{
		return LoadPNG(context);
	}

	return Texture(*this, StringID(), samplerKey);
}

const bool drach::TextureFactory::AddSamplerState(const std::string_view& aName, D3D11_SAMPLER_DESC& aDesc)
{
	ID3D11Device* device = myEngine->GetDevice();
	HRESULT result = device->CreateSamplerState(&aDesc, &mySamplers[StringID(aName.data())]);
	return SUCCEEDED(result);
}







HRESULT CreateDDSTextureFromFile(drach::TextureData& someInfo, drach::TextureInitContext& someData, drach::GraphicsEngine& anEngine)
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
	TextureData info;



	HRESULT r = CreateDDSTextureFromFile(info, someData, *myEngine);
	if (FAILED(r))
	{
		LOG_ERROR("Failed to load dds file from file: " + someData.myName);
		return Texture(*this, StringID(), someData.mySamplerID);
	}

	myTextures[someData.myID] = info;
	LOG("Loaded texture: " + someData.myName + " [Resolution: " + std::to_string(someData.myWidth) + " x " + std::to_string(someData.myHeight) + "]");
	return Texture(*this, someData.myID, someData.mySamplerID);
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

