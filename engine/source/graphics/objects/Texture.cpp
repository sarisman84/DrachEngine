#include "precompile-header/coreIncludes.h"
#include "Texture.h"
#include "graphics/GraphicsEngine.h"
#include "factories/TextureFactory.h"
#include "logging/Logger.h"

drach::Texture::Texture() = default;

drach::Texture::Texture(TextureFactory& aFactory, const StringID anID, const StringID aSamplerID)
	:myID(anID), mySamplerID(aSamplerID)
{
	auto info = aFactory.myTextures[myID];
	myResolution = Vector2f(info.myWidth, info.myHeight);
}

void drach::Texture::Bind(GraphicsEngine& aGraphicsEngine, TextureFactory& aFactory, const uint32_t aSlot)
{

	ID3D11DeviceContext* context = aGraphicsEngine.GetContext();
	context->PSSetSamplers(aSlot, 1, aFactory.mySamplers[mySamplerID].GetAddressOf());
	context->PSSetShaderResources(aSlot, 1, aFactory.myTextures[myID].myResource.GetAddressOf());
}

const drach::Vector2f drach::Texture::Resolution()
{
	return myResolution;
}

const bool drach::Texture::operator==(const Texture& someOtherTexture)
{
	return myID == someOtherTexture.myID;
}

const bool drach::Texture::operator!=(const Texture& someOtherTexture)
{
	return !(*this == someOtherTexture);
}

drach::Texture::operator bool()
{
	return myID != StringID();
}
