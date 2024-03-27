#ifndef TILESHADER
#define TILESHADER

#include "value.fx"
#include "func.fx"

struct VS_IN
{
    float4 vColor : COLOR;
    float3 vPos : POSITION; // Sementic
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
    
    float3 vWorldPos : POSITION;
};

VS_OUT VS_Tile(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    output.vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    
    return output;
}

#define g_Thickness 0.01f
#define FACE_X 12
#define FACE_Y 12
#define TileSize 128
#define ROW g_int_1
#define COL g_int_2


float4 PS_Tile(VS_OUT _in) : SV_Target
{
    float4 vColor = 0.f;
    
    if (g_btex_0)
    {
        float2 FrameSize = float2(1.f / FACE_X, 1.f / FACE_Y);
        float2 FramePosition = float2(ROW, COL);
        
        float2 adjustedUV = FramePosition * FrameSize + _in.vUV * FrameSize;
        vColor = g_tex_0.Sample(g_sam_0, adjustedUV);
    }


    return vColor;
}


#endif