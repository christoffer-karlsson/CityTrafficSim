struct output
{
    float4 Color    : Color;
    float4 Position : SV_Position;
};

cbuffer input
{
    matrix MVP;
};

output main(float3 Position : Position)
{
    output Output;

    Output.Position = mul(float4(Position, 1.0f), MVP);

    Output.Color = float4(1.0f, 1.0f, 0.0f, 0.5f);

    return Output;
}