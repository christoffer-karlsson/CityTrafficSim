struct input
{
    float4 Position : SV_POSITION;
    float3 WorldPosition : WORLDPOSITION;
    float4 Color : COLOR;
    float3 Normal : NORMAL;
    float4 AmbientLight : AMBIENTLIGHT;
    float3 LightPosition : LIGHTPOSITION;
};

static const float3 MaterialColor = float3(0.4f, 0.4f, 0.4f);
static const float3 DiffuseColor = float3(1.0f, 1.0f, 1.0f);
static const float3 Ambient = float3(0.15f, 0.15f, 0.15f);
static const float1 DiffuseIntensity = 1.0f;
static const float1 AttenuationConstant = 1.0f;
static const float1 AttenuationLinear = 0.045f;
static const float1 AttenuationQuad = 0.0075f;


float4 main(input Input) : SV_Target
{
    // Fragment to light vecor data
    const float3 VectorToLight = Input.LightPosition - Input.WorldPosition;
    const float1 DistanceToLight = length(VectorToLight);
    const float3 DirectionToLight = VectorToLight / DistanceToLight;
    
    // Diffuse attenuation
    const float1 Attenuation = 1.0f / (AttenuationConstant + AttenuationLinear * DistanceToLight + AttenuationQuad * (DistanceToLight * DistanceToLight));
    
    // Diffuse intensity
    const float3 Diffuse = DiffuseColor * DiffuseIntensity * Attenuation * max(0.0f, dot(DirectionToLight, Input.Normal));
    
    const float4 Color = float4(saturate(Diffuse + Ambient), 1.0f);

    return Color;
}