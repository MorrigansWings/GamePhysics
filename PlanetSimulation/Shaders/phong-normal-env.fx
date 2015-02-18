// FX Parameters

// transforms
uniform extern float4x4 gWorld;
uniform extern float4x4 gWVP;
uniform extern float4x4 gWorldInverseTranspose;

// toggles
uniform extern int	  useTexture;
uniform extern int	  useNormal;
uniform extern int    useEnvironment;

// diffuse
uniform extern float  gDiffuseCoefficient;
uniform extern float4 gDiffuseMtrl;

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
uniform extern float  gReflectivity;

uniform texture DiffuseTexture;
sampler2D s_2D = sampler_state 
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

uniform extern texture gEnvMap;
sampler EnvMapSampler = sampler_state
{
	Texture = <gEnvMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

struct OutputVS
{
	float4 posH      : POSITION0;
	float2 uvH       : TEXCOORD0;
	float3 posW	     : TEXCOORD1;
	float3 toEyeT	 : TEXCOORD2;
	float3 lightDirT : TEXCOORD3;
	float3 normalH	 : NORMAL0;
	float3 tangentH	 : TANGENT0;
	float3 binormalH : BINORMAL0;
};

// Vertex Shader
//OutputVS PhongVS( float3 posL : POSITION0, float2 uvL : TEXCOORD0, float3 normalL : NORMAL0 )
OutputVS NormalMapVS(	float3 posL		 : POSITION0,
						float2 uvL		 : TEXCOORD0,
						float3 normalL	 : NORMAL0,
						float3 tangentL	 : TANGENT0,
						float3 binormalL : BINORMAL0 )
{
	// Zero out our output
	OutputVS outVS = (OutputVS)0;

	// Build TBN basis
	float3x3 TBN;
	TBN[0] = tangentL;
	TBN[1] = binormalL;
	TBN[2] = normalL;

	// -------- Calculate outVS.posH -----------
	// Transform position to homogenous clip space
	outVS.posH = mul(float4(posL,1.0), gWVP);

	// -------- Calculate outVS.uvH -----------
	// write out the UV coords
	outVS.uvH = uvL;

	// -------- Calculate outVS.posW -----------
	// calculate world position of vertex
	outVS.posW = mul(float4(posL, 1.0f), gWorld).xyz;

	// -------- Calculate outVS.toEyeT -----------
	// Matrix transform to get from object to tangent space
	float3x3 toTangentSpace = transpose(TBN);

	// Convert camera position to local space
	float3 viewerPosL = mul( float4( gViewerPos, 1.0f ), gWorldInverseTranspose ).xyz; 

	// Convert to-eye vector to tangent space
	float3 toEyeL = viewerPosL - posL;
	outVS.toEyeT = mul( toEyeL, toTangentSpace );

	// -------- Calculate outVS.lightDirT -----------
	// Convert light direction to tangent space
	float3 lightDirL = mul( float4( gLightVecW, 0.0f ), gWorldInverseTranspose ).xyz;
	outVS.lightDirT = mul( lightDirL, toTangentSpace );

	// ------- Send out the TBN Span ---------
	outVS.normalH = normalL;
	outVS.binormalH = binormalL;
	outVS.tangentH = tangentL;

	// Done--return the output
	return outVS;
}


// Pixel Shader
//float4 PhongPS( float2 tex : TEXCOORD0, float3 nor : NORMAL0, float3 posW : TEXCOORD1 ) : COLOR
float4 NormalMapPS( float2 tex		 : TEXCOORD0,
					float3 posW		 : TEXCOORD1,
					float3 toEyeT	 : TEXCOORD2,
					float3 lightDirT : TEXCOORD3,
					float3 normal	 : NORMAL0,
					float3 tangent	 : TANGENT0,
					float3 binormal  : BINORMAL0) : COLOR
{
	// ------------ Calculate Pixel Normal --------------

	toEyeT = normalize( toEyeT );
	lightDirT = normalize( lightDirT );

	// Sample the normal map
	float3 nor = float3(0.5, 0.5, 1.0);
	if (useNormal == 1) nor = tex2D(NormalMapSampler, tex);

	// Convert from compressed to true interval (0-1 -> -1-1)
	nor = (2.0f * nor) - 1.0f;
	
	// Normalize to make it a unit vector
	nor = normalize( nor );

	float3x3 tbn;
	float3 n = normalize( mul(gWorld, float4(normal.xyz,0.0)).xyz );
	float3 t = normalize( mul(gWorld, float4(tangent.xyz,0.0)).xyz );
	float3 b = normalize( mul(gWorld, float4(binormal.xyz,0.0)).xyz );
	tbn = float3x3( t, b, n );

	// world space normal
	float3 norW = normalize( mul(tbn, nor) );

	// ------- Get Diffuse Texture --------------//
	float4 textureColor = (float4)1.0;
	if(useTexture == 1) textureColor = tex2D(s_2D, tex);
	
	// ------- Get Reflection Color --------------//
	float4 reflectionColor = (float4)1.0;
	//float3 toEyeW = normalize( gViewerPos - posW );
	float3 envMapTex = reflect(-toEyeT, nor);
	reflectionColor = texCUBE(EnvMapSampler, envMapTex);

	float reflectivity = 0.0;
	if (useEnvironment) reflectivity = gReflectivity;

	//------ Calculate Diffuse Color ----------//
	// zero out the start component
	float4 diffuseComponent = (float4)0.0f;

	// get diffuse color
	float4 diffCoeff = (float4)0;
	float s = max(dot(nor,lightDirT), 0.0f);
	diffCoeff.rgb = (s*gLightColor).rgb;
	diffCoeff.a = 1.0f;

	// calculate material color
	//float4 diffuseMaterialColor = textureColor * gDiffuseMtrl;
	float4 diffuseMaterialColor = ( (1.0-reflectivity) * textureColor * gDiffuseMtrl) + (reflectionColor * reflectivity);

	// get final diffuse
	diffuseComponent = diffCoeff * diffuseMaterialColor;

	//-------Calculate Ambient Color--------//
	// zero out the start component
	float4 ambientComponent = (float4)0.0f;

	// get the combined material color
	float4 ambientMaterialColor = gAmbientMtrl * textureColor;

	// combine the ambient material color with the ambient light color
	ambientComponent = ambientMaterialColor * gLightColor;

	//-------Calculate Specular Color-------//
	// zero out the start component
	float4 specularComponent = (float4)0.0f;

	// calculate the spec reflection vector
	//float3 lightVecW = normalize( gLightVecW );
	float3 reflection = reflect(-lightDirT, nor);

	// determine how much spec light gets to the viewer's eye
	float spec = pow(max(dot(toEyeT, reflection), 0.0f), gSpecularPower);

	// kill spec if diffuse is low
	if(s <= 0.0f)
	     spec = 0.0f;

	// get the combined material color
	//float4 specularMaterialColor = (gSpecularMtrl * 1-reflectivity) + (reflectionColor * reflectivity);
	float4 specularMaterialColor = gSpecularMtrl;

	// combine the material and light color with the specular power (spec)
	specularComponent = spec * gLightColor * specularMaterialColor;

	//--------Calculate Final Color--------//
	float4 finalColor = (diffuseComponent * gDiffuseCoefficient); +  // diffuse
						(ambientComponent * gAmbientCoefficient) +  // ambient
						(specularComponent * gSpecularCoefficient); // specular

	return finalColor;
}

float4 WireframePS() : COLOR
{
	return (float4)0.0;
}

technique PhongTech
{
	pass P0
	{
		// specify the vertex and pixel shader associated with this pass
		vertexShader = compile vs_3_0 NormalMapVS();
		pixelShader  = compile ps_3_0 NormalMapPS();

		FillMode = Solid;
	}

	pass P1
	{
		// specify the vertex and pixel shader associated with this pass
		vertexShader = compile vs_3_0 NormalMapVS();
		pixelShader  = compile ps_3_0 WireframePS();

		FillMode = Wireframe;
	}
}

