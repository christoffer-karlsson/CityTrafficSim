struct Input
{
	float4 Position				: SV_POSITION;
	float2 TextureCoordinate	: TEXCOORD;
	float4 AmbientLight			: AMBLIGHT;
};

Texture2D Texture;

SamplerState Sampler;

float4 main(Input In) : SV_Target
{
	float4 Color = Texture.Sample(Sampler, In.TextureCoordinate);

	float4 Blend = Color * In.AmbientLight;

	return Blend;
}