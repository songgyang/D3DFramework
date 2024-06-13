#include "Common.hlsl"

struct VertexInput
{
    float4 Position : POSITION0;
	float4 Color : COLOR0;		//base color -> albedo
	float3 Normal : NORMAL0;
};
struct PixelInput
{
    float4 Position : SV_POSITION;
	float4 Color : COLOR0;
    float4 wPosition : POSITION0;
	float3 Normal : NORMAL0;
};

PixelInput VS(VertexInput input)
{
   
    PixelInput output;
	output.Color = input.Color;
    //  o           =  i X W
    output.Position = mul(input.Position, World);
	output.wPosition = output.Position;
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Proj);
	output.Normal = mul(input.Normal, (float3x3) World);
    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
	float4 BaseColor = Lighting(input.Color, float2(1, 1), normalize(input.Normal), input.wPosition.xyz);
	
	//float3 normal = normalize(input.Normal);
	//float3 dirLight = normalize(DirLight.xyz);
	//float D = saturate(dot(normal, -dirLight));
	
	//float3 reflection = reflect(dirLight, normal);
	//float3 lookDir = normalize(input.wPosition.xyz - ViewPos.xyz);
	//float S = saturate(dot(reflection, -lookDir));
	//S = pow(S, 30.0f);
	
	
	
	
	//float4 BaseColor = input.Color;
	
	////                       µðÇ»Áî +      ¾Úºñ¾ðÆ®            + ½ºÆåÅ§·¯
	//BaseColor.rgb = (BaseColor.rgb * Kd.rgb * D)
	//+ (BaseColor.rgb * Ka.rgb * 0.2f) + (float3(1, 1, 1) * Ks.rgb * S);
	
	
	return BaseColor;
}