struct input
{
    float4 Position         : SV_POSITION;
    float4 Color            : COLOR;
    float1 IsHighlighted    : ISHIGHLIGHTED;
};

float4 main(input Input) : SV_Target
{
    float4 Color = Input.Color;
    
    if (Input.IsHighlighted > 0.0f)
    {
        Color = Color * float4(2.0f, 2.0f, 2.0f, 1.0f);
    }
    
    return Color;
}