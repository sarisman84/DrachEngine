#pragma once
#include <cstdint>
#include "util/math/Vector2.h"
#include "util/other/StringID.h"
namespace drach
{
	class TextureFactory;
	class GraphicsEngine;
	class Texture
	{

	public:
		Texture();
		Texture(TextureFactory& aFactory, const StringID anID, const StringID aSamplerID);
		void Bind(GraphicsEngine& aGraphicsEngine, TextureFactory& aFactory, const uint32_t aSlot);

		const Vector2f Resolution();

		const bool operator==(const Texture& someOtherTexture);
		const bool operator!=(const Texture& someOtherTexture);


		inline const StringID GetID() const noexcept { return myID; }


		operator bool();

	private:
		StringID myID;
		StringID mySamplerID;
		Vector2f myResolution;
	};
}