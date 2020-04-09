struct input
{
    float3 Position         : POSITION;
    float4 Color            : COLOR;
    float1 IsHighlighted    : ISHIGHLIGHTED;
};

struct output
{
    float4 Position         : SV_POSITION;
    float4 Color            : COLOR;
    float1 IsHighlighted    : ISHIGHLIGHTED;
};

output main(input Input)
{
    output Output;

    Output.Position = float4(Input.Position, 1.0f);
    Output.Color = Input.Color;
    Output.IsHighlighted = Input.IsHighlighted;

    return Output;
}