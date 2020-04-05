struct input
{
	float4 Position				: SV_POSITION;
	float4 Color				: COLOR;
};

float4 main(input Input) : SV_Target
{
	return Input.Color;
}