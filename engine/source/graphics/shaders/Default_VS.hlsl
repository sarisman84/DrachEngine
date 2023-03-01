#include "util/ShaderStructs.hlsli"
#include "util/ShaderBuffers.hlsli"

PixelInputType main(VertexInputType someInput)
{
    PixelInputType result;
    
    float4 vertexObjectPos = float4(someInput.myPosition, 1);
    float4 vertexWorldPos = mul(myModelMatrix, vertexObjectPos);
    float4 vertexClipPos = mul(myViewMatrix, vertexWorldPos);
    
    result.myPosition = vertexClipPos;
    result.myUV = someInput.myUV;
    
    return result;
}