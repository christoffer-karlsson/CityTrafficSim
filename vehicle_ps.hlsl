struct input
{
    float4 Position : SV_POSITION;
    float3 ModelPosition : MODELPOSITION;
    float4 MaterialColor : COLOR;
    float3 Normal : NORMAL;
    float4 AmbientLight : AMBIENTLIGHT;
    float3 LightPosition : LIGHTPOSITION;
};

static const float3 DiffuseColor = float3(1.0f, 1.0f, 1.0f);
static const float3 Ambient = float3(0.15f, 0.15f, 0.20f);
static const float1 DiffuseIntensity = 0.5f;
static const float1 AttenuationConstant = 1.0f;
static const float1 AttenuationLinear = 0.0014f;
static const float1 AttenuationQuad = 0.000007f;


float4 main(input Input) : SV_Target
{
    // Fragment to light vecor data
    const float3 VectorToLight = Input.LightPosition - Input.ModelPosition;
    const float1 DistanceToLight = length(VectorToLight);
    const float3 DirectionToLight = VectorToLight / DistanceToLight;
    
    // Diffuse attenuation
    const float1 Attenuation = 1.0f / (AttenuationConstant + AttenuationLinear * DistanceToLight + AttenuationQuad * (DistanceToLight * DistanceToLight));
    
    // Diffuse intensity
    const float3 Diffuse = DiffuseColor * DiffuseIntensity * Attenuation * max(0.0f, dot(DirectionToLight, Input.Normal));
    
    // NOTE(Cristoffer): Put everything together for final pixel color.
    float4 Color = float4(saturate(Diffuse + Ambient) * Input.MaterialColor, 1.0f);

    // NOTE(Cristoffer): Add alpha in the end to be able to control transparency.
    float Alpha = Input.MaterialColor.w;
    Color = Color * float4(1.0f, 1.0f, 1.0f, Alpha);
    
    return Color;
}