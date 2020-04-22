struct input
{
    float3 Position         : POSITION;
    float3 Normal           : NORMAL;
    float3 UV               : TEXCOORD;
    float4 Color            : COLOR;
    float4 HightlightColor  : HIGHLIGHTCOLOR;
};

struct instanced_input
{
    row_major matrix Model  : INSTANCE_MODEL_MATRIX;
    float4 Color            : INSTANCE_COLOR;
};

struct output
{
    float4 Position         : SV_POSITION;
    float3 Normal           : NORMAL;
    float2 UV               : TEXCOORD;
    float4 Color            : COLOR;
    float4 HightlightColor  : HIGHLIGHTCOLOR;
    float3 ModelPosition    : MODELPOSITION;
};

cbuffer transformation_constants
{
    row_major matrix ViewProjection;
};

output main(input Input, instanced_input Instance, uint InstanceID : SV_InstanceID)
{
    output Output;
    
    matrix MVP = mul(Instance.Model, ViewProjection);
    
    Output.Position = mul(float4(Input.Position, 1.0f), MVP);
    Output.Normal = mul(Input.Normal, (float3x3) Instance.Model);
    Output.ModelPosition = (float3) mul(float4(Input.Position, 1.0f), Instance.Model);
    
    Output.HightlightColor = Input.HightlightColor;
    Output.Color = Instance.Color;
    Output.UV = float2(Input.UV.x, Input.UV.y);
    
    return Output;
}