struct input
{
	float3 Position				: POSITION;
	float2 TextureCoordinate	: TEXCOORD;
	float4 AmbientLight			: AMBLIGHT;
};

struct output
{
	float4 Position				: SV_POSITION;
	float2 TextureCoordinate	: TEXCOORD;
	float4 AmbientLight			: AMBLIGHT;
};

cbuffer constantbuffer
{
    matrix MVP;
	float4 AmbientLight;
};

output main(input Input)
{
	output Output;

	Output.Position = mul(float4(Input.Position, 1.0f), MVP);

    Output.TextureCoordinate = Input.TextureCoordinate;

    Output.AmbientLight = AmbientLight;

    return Output;
}