#pragma once
#include <cstdint>

namespace drach
{
	class GraphicsEngine;
	class Texture
	{
		
	public:
		Texture();
		Texture(TextureFactory& aFactory, const uint32_t anID);
		void Bind(GraphicsEngine& aGraphicsEngine, const uint32_t aSlot);

		const bool operator==(const Texture& someOtherTexture);
		const bool operator!=(const Texture& someOtherTexture);

	private:
		TextureFactory* myFactory;
		uint32_t myID;
	};
}