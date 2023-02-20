#include "util/ShaderStructs.hlsli"
#include "util/ShaderBuffers.hlsli"

PixelInputType main(VertexInputType someInput )
{
    PixelInputType result;
    
    float4 vertexObjectPos = someInput.myPosition;
    float4 vertexWorldPos = mul(myModelMatrix, vertexObjectPos);
    float4 vertexClipPos = mul(myViewMatrix, vertexWorldPos);
    
    result.myPosition = vertexClipPos;
    result.myColor = float4(1, 1, 1, 1);
    
    return result;
}