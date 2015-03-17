// FX Parameters

// transforms
uniform extern float4x4 gWorld;
uniform extern float4x4 gWVP;
uniform extern float4x4 gWorldInverseTranspose;

// diffuse
uniform extern float  gDiffuseCoefficient;
uniform extern float4 gDiffuseMtrl;
uniform extern int	  useTexture;

// ambient
uniform extern float  gAmbientCoefficient;
uniform extern float4 gAmbientMtrl;

// specular
uniform extern float  gSpecularCoefficient;
uniform extern float4 gSpecularMtrl;
uniform extern float  gSpecularPower;

// lighting
uniform extern float3 gLightVecW;
uniform extern float3 gViewerPos;
uniform extern float4 gLightColor;

uniform extern texture DiffuseTexture;
sampler TexSampler = sampler_state
{
	Texture = <DiffuseTexture>;
	MinFilter = ANISOTROPIC;
	MaxAnisotropy = 8;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

uniform extern texture gNormalMap;
sampler NormalMapSampler = sampler_state
{
	Texture = <gNormalMap>;
	MinFilter = ANISOTROPIC;
	MaxAnisotropy = 8;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

struct OutputVS
{
	float4 posH			:POSITION0;
	float3 toEyeT		:TEXCOORD0;
	float3 lightDirT	:TEXCOORD1;
	float2 tex			:TEXCOORD2;
};

OutputVS NormalMapVS(	float3 posL		: POSITION0,
						float2 tex		: TEXCOORD0,
						float3 normL	: NORMAL0,
						float3 tanL		: TANGENT0,
						float3 binormL	: BINORMAL0 )
{
	// Zero the output
	OutputVS outVS = (OutputVS)0;

	// Build TBN basis
	float3x3 TBN;
	TBN[0] = tanL;
	TBN[1] = binormL;
	TBN[2] = normL;

	// Matrix transform to get from object to tangent space
	float3x3 toTangentSpace = transpose(TBN);

	// Convert camera position to local space
	float3 viewerPosL = mul( float4( gViewerPos, 1.0f ), gWorld ); 

	// Convert to-eye vector to tangent space
	float3 toEyeL = viewerPosL - posL;
	outVS.toEyeT = mul( toEyeL, toTangentSpace );

	// Convert light direction to tangent space
	float3 lightDirL = mul( float4( gLightVecW, 0.0f ), gWorld ).xyz;
	outVS.lightDirT = mul( lightDirL, toTangentSpace );

	// Convert to homogeneous clip space
	outVS.posH = mul(float4(posL,1.0), gWVP);

	// Pass on texture coords to be interpolated in rasterization
	outVS.tex = tex;

	return outVS;
}

float4 NormalMapPS( float3 toEyeT		: TEXCOORD0,
					float3 lightDirT	: TEXCOORD1,
					float2 tex			: TEXCOORD2 ) : COLOR
{
	// Normalize
	toEyeT = normalize( toEyeT );
	lightDirT = normalize( lightDirT );

	// Light vector is opposite the direction of the light
	float3 lightVecT = -lightDirT;

	// Sample the normal map
	float3 normalT = tex2D(NormalMapSampler, tex);

	// Convert from compressed to true interval (0-1 -> -1-1)
	normalT = 2.0f * normalT - 1.0f;
	
	// Normalize to make it a unit vector
	normalT = normalize( normalT );

	// Calculate the reflection vector
	float3 r = reflect( -lightVecT, normalT );

	// Calculate amount of spec light gets to the eye
	float s = pow( max( dot( r, toEyeT ), 0.0f ), gSpecularPower );

	// Calculate diffuse light intensity hitting the vertex
	float d = max( dot( lightVecT, normalT ), 0.0f );

	// Kill spec lighting if diffuse is too low
	if( d <= 0.0f )
		s = 0.0f;

	// Calculate ambient, diffuse and specular terms
	//float3 spec = s * ( gSpecularMtrl * gSpecularCoefficient ).rgb;
	//float3 diffuse = d * (gDiffuseMtrl * gDiffuseCoefficient ).rgb;
	//float3 ambient = gAmbientMtrl * gAmbientCoefficient;

	// Get texture color
	float4 texColor = (float4)1.0;
	if(useTexture == 1) texColor = tex2D(TexSampler, tex);

	float3 spec = s * gSpecularMtrl.rgb;
	float3 diff = d * gDiffuseMtrl * texColor.rgb;
	float3 ambi = gAmbientMtrl * texColor.rgb;

	// Combine lighting and texture colors
	float3 color = (gAmbientCoefficient * ambi) +
				   (gDiffuseCoefficient * diff) +
				   (gSpecularCoefficient * spec);

	return float4( color, gDiffuseMtrl.a * texColor.a );
}

float4 WireframePS() : COLOR
{
	return (float4)0.0;
}

technique NormalMapTechnique
{
	pass P0
	{
		vertexShader = compile vs_3_0 NormalMapVS();
		pixelShader = compile ps_3_0 NormalMapPS();

		FillMode = Solid;
	}

	pass P1
	{
		vertexShader = compile vs_3_0 NormalMapVS();
		pixelShader = compile ps_3_0 WireframePS();

		FillMode = Wireframe;
	}
}