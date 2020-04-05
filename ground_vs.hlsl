struct input
{
	float3 Position				: POSITION;
    float2 UV					: TEXCOORD;
};

struct output
{
	float4 Position				: SV_POSITION;
    float2 UV					: TEXCOORD;
};

cbuffer ConstantBuffer
{
	matrix MVP;
};

output main( input Input )
{
	output Output;

	Output.Position = float4(Input.Position, 1.0f);
	Output.Position = mul(Output.Position, MVP);

	Output.UV = Input.UV;

	return Output;
}