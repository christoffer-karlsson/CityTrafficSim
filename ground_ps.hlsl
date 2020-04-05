struct input
{
	float4 Position	: SV_POSITION;
    float2 UV		: TEXCOORD;
};

Texture2D Texture;

SamplerState Sampler;

float4 main(input Input) : SV_Target
{
    float4 Color = Texture.Sample(Sampler, Input.UV);

    return Color;
}