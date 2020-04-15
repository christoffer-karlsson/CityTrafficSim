struct input
{
    float3 Position : POSITION;
    float3 Normal : NORMAL;
    float2 UV : TEXCOORD;
    float4 HightlightColor : HIGHLIGHTCOLOR;
};

struct output
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD;
    float3 ModelPosition : MODELPOSITION;
    float3 Normal : NORMAL;
    float4 AmbientLight : AMBIENTLIGHT;
    float3 LightPosition : LIGHTPOSITION;
    float4 HightlightColor : HIGHLIGHTCOLOR;
};


cbuffer constantbuffer
{
    matrix MVP;
    matrix Model;
    float4 AmbientLight;
    float3 LightPosition;
};

output main(input Input)
{
    output Output;

    Output.ModelPosition = (float3) mul(float4(Input.Position, 1.0f), Model);
    
    Output.Normal = mul(Input.Normal, (float3x3) Model);

    Output.Position = mul(float4(Input.Position, 1.0f), MVP);
    
    Output.UV = Input.UV;
    
    Output.HightlightColor = Input.HightlightColor;
    
    Output.LightPosition = LightPosition;
    
    Output.AmbientLight = AmbientLight;

    return Output;
}