struct input
{
    float3 Position : POSITION;
    float4 Color    : COLOR;
    float3 Normal   : NORMAL;
};

struct output
{
    float4 Position      : SV_POSITION;
    float3 WorldPosition : WORLDPOSITION;
    float4 Color         : COLOR;
    float3 Normal        : NORMAL;
    float4 AmbientLight  : AMBIENTLIGHT;
    float3 LightPosition : LIGHTPOSITION;
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

    Output.WorldPosition = (float3)mul(float4(Input.Position, 1.0f), Model);
    
    Output.Normal = mul(Input.Normal, (float3x3)Model);

    Output.Position = mul(float4(Input.Position, 1.0f), MVP);
    
    Output.Color = Input.Color;
    
    Output.LightPosition = LightPosition;
    
    Output.AmbientLight = AmbientLight;

    return Output;
}