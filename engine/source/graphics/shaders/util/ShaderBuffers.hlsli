cbuffer FrameBuffer : register(b0)
{
    float4x4 myViewMatrix;
}

cbuffer ObjectBuffer : register(b1)
{
    float4x4 myModelMatrix;
}