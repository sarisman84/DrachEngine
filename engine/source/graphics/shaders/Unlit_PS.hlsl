#include "util/ShaderStructs.hlsli"
#include "util/ShaderBuffers.hlsli"

Texture2D aTexture : register(t0);
SamplerState aSampler : register(s0);


PixelOutput main(PixelInputType input)
{
    PixelOutput result;
    result.myColor = aTexture.Sample(aSampler, input.myUV).rgba;
    return result;

}