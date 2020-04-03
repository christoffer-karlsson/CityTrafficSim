struct Input
{
	float3 Position				: POSITION;
	float2 TextureCoordinate	: TEXCOORD;
	float4 AmbientLight			: AMBLIGHT;
};

struct Output
{
	float4 Position				: SV_POSITION;
	float2 TextureCoordinate	: TEXCOORD;
	float4 AmbientLight			: AMBLIGHT;
};

cbuffer ConstantBuffer
{
	matrix MVP;
	float4 AmbientLight;
};

Output main(Input In)
{
	Output Out;

	Out.Position = mul(float4(In.Position, 1.0f), MVP);

	Out.TextureCoordinate = In.TextureCoordinate;

	Out.AmbientLight = AmbientLight;

	return Out;
}