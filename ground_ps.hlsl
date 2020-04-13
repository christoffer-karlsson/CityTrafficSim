struct input
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD;
    float3 ModelPosition : MODELPOSITION;
    float3 Normal : NORMAL;
    float4 AmbientLight : AMBIENTLIGHT;
    float3 LightPosition : LIGHTPOSITION;
    float1 IsPicked : ISPICKED;
};

Texture2D Texture;

SamplerState Sampler;

static const float3 DiffuseColor = float3(1.0f, 1.0f, 1.0f);
static const float3 Ambient = float3(0.15f, 0.15f, 0.20f);
static const float1 DiffuseIntensity = 1.0f;
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
    
    float4 TextureColor = Texture.Sample(Sampler, Input.UV);
    
    float4 Color = float4(saturate(Diffuse + Ambient) * TextureColor, 1.0f);
    
    if (Input.IsPicked > 0.0f)
    {
        // NOTE(Cristoffer): If pixel is marked as picked, do the extra coloring here.
        Color = Color * float4(1.3f, 1.3f, 1.3f, 1.0f);
    }
    
    return Color;
}