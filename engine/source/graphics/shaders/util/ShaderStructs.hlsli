struct VertexInputType
{
    float3 myPosition : POSITION;
    float2 myUV : TEXCOORD;
};

struct PixelInputType
{
    float4 myPosition : SV_POSITION;
    float4 myColor : COLOR;
};

struct PixelOutput
{
    float4 myColor : SV_TARGET;
};