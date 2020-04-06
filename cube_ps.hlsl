struct input
{
	float4 Position				: SV_POSITION;
	float2 TextureCoordinate	: TEXCOORD;
	float4 AmbientLight			: AMBLIGHT;
};

Texture2D Texture;

SamplerState Sampler;

float4 main(input Input) : SV_Target
{
    float4 Color = Texture.Sample(Sampler, Input.TextureCoordinate);

    float4 Blend = Color * Input.AmbientLight;

	return Blend;
}