#pragma once
#include <unordered_map>
#include <string_view>
#include "graphics/DirectX11/DXTypes.h"
#include "graphics/objects/Texture.h"
#include "DirectXTex/DDSTextureLoader/DDSTextureLoader11.h"

#include <filesystem>

namespace drach
{
	struct TextureInitContext
	{
		std::string myName;
		std::filesystem::path myFilePath;
		uint32_t myID;
		uint32_t myWidth;
		uint32_t myHeight;
		void* myPixelData;
	};


	class GraphicsEngine;
	class TextureFactory
	{
		friend class Texture;
	public:
		TextureFactory(GraphicsEngine& aGraphicsEngine);
		Texture GetTexture(const std::string_view& aFile);
	private:
		Texture LoadDDS(TextureInitContext& someData);
		Texture LoadPNG(TextureInitContext& someData);

		RenderResource ConstructShaderResource(const D3D11_TEXTURE2D_DESC& aDescription, TextureInitContext& someData);

	private:
		std::unordered_map<uint32_t, RenderResource> myTextures;
		GraphicsEngine* myEngine;
	};
}