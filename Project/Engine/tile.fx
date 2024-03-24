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

float4 PS_Tile(VS_OUT _in) : SV_Target
{
    float4 vColor = 0.f;
    
    if (g_btex_0)
    {
        vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
        
        return vColor;
    }
    
    if (g_int_0 == 1)
    {
        if (g_Thickness <= _in.vUV.x && _in.vUV.x <= (1.f - g_Thickness)
        && g_Thickness <= _in.vUV.y && _in.vUV.y <= (1.f - g_Thickness))
        {
            discard;
        }
        vColor = float4(0.f, 0.f, 1.f, 1.f);
    }
    
    return vColor;
}


#endif