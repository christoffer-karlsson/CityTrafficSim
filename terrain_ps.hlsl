struct input
{
    float4 Position : SV_POSITION;
    float3 Normal : NORMAL;
    float2 UV : TEXCOORD;
    float4 Color : COLOR;
    float4 HightlightColor : HIGHLIGHTCOLOR;
    float3 ModelPosition : MODELPOSITION;
};

cbuffer light_constants
{
    float3 LightPosition;
    float3 Ambient;
    float3 DiffuseColor;
    
    float1 DiffuseIntensity;
    float1 AttenuationConstant;
    float1 AttenuationLinear;
    float1 AttenuationQuad;
};

Texture2D Texture;
SamplerState Sampler;

float4 main(input Input) : SV_Target
{
    // Fragment to light vecor data
    const float3 VectorToLight = LightPosition - Input.ModelPosition;
    const float1 DistanceToLight = length(VectorToLight);
    const float3 DirectionToLight = VectorToLight / DistanceToLight;
    
    // Diffuse attenuation
    const float1 Attenuation = 1.0f / (AttenuationConstant + AttenuationLinear * DistanceToLight + AttenuationQuad * (DistanceToLight * DistanceToLight));
    
    // Diffuse intensity
    const float3 Diffuse = DiffuseColor * DiffuseIntensity * Attenuation * max(0.0f, dot(DirectionToLight, Input.Normal));
    
    // Texture sampling as color value
    float4 TextureColor = Texture.Sample(Sampler, Input.UV);
    
    float4 Color = float4(saturate(Diffuse + Ambient) * TextureColor, 1.0f);
    
    // Add highlight color
    Color = Color * Input.HightlightColor;

    return Color;
}