struct input
{
    float3 Position : POSITION;
    float3 Normal : NORMAL;
    float2 UV : TEXCOORD;
    float4 Color : COLOR;
    float4 HightlightColor : HIGHLIGHTCOLOR;
};

struct output
{
    float4 Position : SV_POSITION;
    float3 Normal : NORMAL;
    float2 UV : TEXCOORD;
    float4 Color : COLOR;
    float4 HightlightColor : HIGHLIGHTCOLOR;
    float3 ModelPosition : MODELPOSITION;
};

cbuffer transformation_constants
{
    matrix MVP;
    matrix Model;
};

output main(input Input)
{
    output Output;

    Output.Position = mul(float4(Input.Position, 1.0f), MVP);
    Output.Normal = mul(Input.Normal, (float3x3) Model);
    Output.ModelPosition = (float3) mul(float4(Input.Position, 1.0f), Model);
    
    Output.HightlightColor = Input.HightlightColor;
    Output.Color = Input.Color;
    Output.UV = Input.UV;
    
    return Output;
}