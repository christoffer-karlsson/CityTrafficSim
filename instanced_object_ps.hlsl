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
    float1 byte_pad_1;
    float3 Ambient;
    float1 byte_pad_2;
    float3 DiffuseColor;
    float1 byte_pad_3;
    
    float1 DiffuseIntensity;
    float1 AttenuationConstant;
    float1 AttenuationLinear;
    float1 AttenuationQuad;
};

float4 main(input Input) : SV_Target
{ 
    // Fragment to light vecor data
    float3 VectorToLight = LightPosition - Input.ModelPosition;
    float1 DistanceToLight = length(VectorToLight);
    float3 DirectionToLight = VectorToLight / DistanceToLight;
    
    // Diffuse attenuation
    float1 Attenuation = 1.0f / (AttenuationConstant + AttenuationLinear * DistanceToLight + AttenuationQuad * (DistanceToLight * DistanceToLight));
    
    // Diffuse intensity
    float3 Diffuse = DiffuseColor * DiffuseIntensity * Attenuation * max(0.0f, dot(DirectionToLight, Input.Normal));
    
    float4 Color = float4(saturate(Diffuse + Ambient) * (float3)Input.Color, 1.0f);
    
    // Add highlight color and transparency
    Color = Color * Input.HightlightColor * float4(1.0f, 1.0f, 1.0f, Input.Color.w);

    return Color;
}