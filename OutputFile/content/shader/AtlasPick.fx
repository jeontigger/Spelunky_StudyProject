#ifndef ATLASSHADER
#define ATLASSHADER

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

VS_OUT VS_ATLAS(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    output.vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    
    return output;
}

#define g_Thickness 0.01f
#define g_Width g_float_0
#define g_Height g_float_1
#define SliceWidth g_int_0
#define SliceHeight g_int_1
#define g_GridRow g_float_2
#define g_GridCol g_float_3
#define Atlas g_tex_0


float4 PS_ATLAS(VS_OUT _in) : SV_Target
{
    float4 vColor = 0.f;
    
    if (g_btex_0)
    {
        
        float2 FrameSize = float2(1.f / SliceWidth, 1.f / SliceHeight);
        float2 FramePosition = float2(g_GridRow, g_GridCol);
        float2 adjustedUV = FramePosition * FrameSize + _in.vUV * FrameSize;
        vColor = Atlas.Sample(g_sam_1, adjustedUV);
        
        float sum = vColor.r + vColor.g + vColor.b;
        
        if (sum < 0.1f)
        {
            discard;
        }

        if (vColor.a < 0.01f)
        {
        // ÇÈ¼¿ ½¦ÀÌ´õ¸¦ Áß°£¿¡ Æó±âÃ³¸®
            discard; //clip(-1);
        }
    }
    return vColor;
}


#endif