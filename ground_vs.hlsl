struct input
{
	float3 Position	: POSITION;
    float2 UV		: TEXCOORD;
    float1 IsPicked	: ISPICKED;
};

struct output
{
	float4 Position	: SV_POSITION;
    float2 UV		: TEXCOORD;
    float1 IsPicked	: ISPICKED;
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
	
    Output.IsPicked = Input.IsPicked;

	return Output;
}