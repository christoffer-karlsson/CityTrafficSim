struct input
{
	float3 Position				: POSITION;
	float4 Color				: COLOR;
};

struct output
{
	float4 Position				: SV_POSITION;
	float4 Color				: COLOR;
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

	Output.Color = Input.Color;

	return Output;
}