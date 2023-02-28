#include "precompile-header/coreIncludes.h"
#include "Texture.h"
#include "graphics/GraphicsEngine.h"
#include "factories/TextureFactory.h"
#include "logging/Logger.h"

drach::Texture::Texture() = default;

drach::Texture::Texture(TextureFactory& aFactory, const uint32_t anID)
	:myFactory(&aFactory), myID(anID)
{
}

void drach::Texture::Bind(GraphicsEngine& aGraphicsEngine, const uint32_t aSlot)
{
	ID3D11DeviceContext* context = aGraphicsEngine.GetContext();
	context->PSSetShaderResources(aSlot, 1, myFactory->myTextures[myID].GetAddressOf());
}

const bool drach::Texture::operator==(const Texture& someOtherTexture)
{
	return myID == someOtherTexture.myID;
}

const bool drach::Texture::operator!=(const Texture& someOtherTexture)
{
	return !(*this == someOtherTexture);
}
