// HLSL에서 상수 버퍼 데이터 정의
cbuffer CBufferObject
{
    float4x4 gWorld;
    float4x4 gWorldViewProj;
};

struct VertexIn
{
    float3 PosL : POSITION;
};

struct VertexOut
{
    float4 PosH : SV_POSITION;
};

VertexOut VS(VertexIn vin) : SV_POSITION
{
    VertexOut vout;
    vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}