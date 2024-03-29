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
#define ROW g_int_2
#define COL g_int_1
#define Type g_int_0 // 2: tree, 3: º®, 6: ¹Ýº® 9: Door
#define DwellingTex g_tex_0
#define WoodTex g_tex_1
#define WallTex g_tex_2
#define FloorTex g_tex_3

float4 PS_Tile(VS_OUT _in) : SV_Target
{
    float4 vColor = 0.f;
    
    if (g_btex_0 && g_btex_1 && g_btex_2)
    {
        float2 FrameSize = float2(1.f / FACE_X, 1.f / FACE_Y);
        float2 FramePosition = float2(ROW, COL);
        
        float2 adjustedUV = FramePosition * FrameSize + _in.vUV * FrameSize;
        if (Type == 2)
        {
            FrameSize = float2(1.f / 10.f, 1.f / 10.f);
            float2 adjustedUV = FramePosition * FrameSize + _in.vUV * FrameSize;
            vColor = WoodTex.Sample(g_sam_1, adjustedUV);
        }
        else if (Type == 3)
        {
            FrameSize = float2(1.f / 8.f, 1.f / 8.f);
            float2 adjustedUV = FramePosition * FrameSize + _in.vUV * FrameSize;
            vColor = WallTex.Sample(g_sam_1, adjustedUV);
        }
        else if (Type == 6)
        {
            FrameSize = float2(1.f / 8.f, 1.f / 8.f);
            float2 adjustedUV = FramePosition * FrameSize + _in.vUV * FrameSize;
            vColor = FloorTex.Sample(g_sam_1, adjustedUV);
        }
        else if (Type == 9)
        {
            FrameSize = float2(1.f / 4, 1.f / 6);
            FramePosition = float2(0, 3.5);
            float2 adjustedUV = FramePosition * FrameSize + _in.vUV * FrameSize;
            vColor = DwellingTex.Sample(g_sam_1, adjustedUV);
        }

        else
        {
            float2 adjustedUV = FramePosition * FrameSize + _in.vUV * FrameSize;
            vColor = DwellingTex.Sample(g_sam_1, adjustedUV);
        }
        
        if (vColor.a < 0.1f)
        {
            // ÇÈ¼¿ ½¦ÀÌ´õ¸¦ Áß°£¿¡ Æó±âÃ³¸®
            discard; //clip(-1);            
        }

    }
    return vColor;
}


#endif