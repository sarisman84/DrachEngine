#pragma once
#include <unordered_map>
#include <string_view>
#include "graphics/DirectX11/DXTypes.h"
#include "graphics/objects/Texture.h"
#include "DirectXTex/DDSTextureLoader/DDSTextureLoader11.h"
#include "util/other/StringID.h"
#include <filesystem>

#define SAMPLER_DEFAULT_WRAP "Default_Wrap"

namespace drach
{
	struct TextureInitContext
	{
		std::string myName;
		std::filesystem::path myFilePath;
		StringID myID;
		StringID mySamplerID;
		uint32_t myWidth;
		uint32_t myHeight;
		void* myPixelData;
	};

	struct TextureData
	{
		RenderResource myResource;
		uint32_t myWidth;
		uint32_t myHeight;

	};


	class GraphicsEngine;
	class TextureFactory
	{


		friend class Texture;
	public:
		TextureFactory(GraphicsEngine& aGraphicsEngine);
		Texture GetTexture(const std::string_view& aFile, const std::string_view& aSamplerName = SAMPLER_DEFAULT_WRAP);

		const bool AddSamplerState(const std::string_view& aName, D3D11_SAMPLER_DESC& aDesc);

	private:
		Texture LoadDDS(TextureInitContext& someData);
		Texture LoadPNG(TextureInitContext& someData);

		RenderResource ConstructShaderResource(const D3D11_TEXTURE2D_DESC& aDescription, TextureInitContext& someData);


	private:
		std::unordered_map<StringID, TextureData, StringIDHash> myTextures;
		std::unordered_map<StringID, SamplerState, StringIDHash> mySamplers;
		GraphicsEngine* myEngine;
		SamplerState myCurrentSampler;
	};

}