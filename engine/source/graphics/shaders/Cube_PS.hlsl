#include "util/ShaderStructs.hlsli"
#include "util/ShaderBuffers.hlsli"

PixelOutput main(PixelInputType input)
{
    PixelOutput result;
    result.myColor = input.myColor;
    return result;

}