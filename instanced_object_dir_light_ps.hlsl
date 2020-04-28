struct input
{
    float4 Position : SV_POSITION;
    float3 Normal : NORMAL;
    float2 UV : TEXCOORD;
    float4 Color : COLOR;
    float4 HightlightColor : HIGHLIGHTCOLOR;
    float3 ModelPosition : MODELPOSITION;
};

cbuffer light_constants
{
    float3 LightDirection;
    float1 byte_pad_1;
    float4 LightAmbient;
    float4 LightDiffuse;
};

float4 main(input Input) : SV_Target
{
    Input.Normal = normalize(Input.Normal);

    //float4 Diffuse = ObjTexture.Sample(ObjSamplerState, input.TexCoord);

    float4 Diffuse = Input.Color;
    
    float3 finalColor;

    finalColor = Diffuse * LightAmbient;
    finalColor += saturate(dot(LightDirection, Input.Normal) * LightDiffuse * Diffuse);
    
    return float4(finalColor, Diffuse.a);
}