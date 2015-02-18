// FX Parameters

// transforms
uniform extern float4x4 gWorld;
uniform extern float4x4 gWVP;
uniform extern float4x4 gWorldInverseTranspose;

// toggles
uniform extern int	  useTexture;
uniform extern int	  useNormal;

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

struct OutputVS
{
	float4 posH      : POSITION0;
	float2 uvH       : TEXCOORD0;
	float3 posW	     : TEXCOORD1;
	float3 toEyeT	 : TEXCOORD2;
	float3 lightDirT : TEXCOORD3;
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

	// Done--return the output
	return outVS;
}


// Pixel Shader
//float4 PhongPS( float2 tex : TEXCOORD0, float3 nor : NORMAL0, float3 posW : TEXCOORD1 ) : COLOR
float4 NormalMapPS( float2 tex		 : TEXCOORD0,
					float3 posW		 : TEXCOORD1,
					float3 toEyeT	 : TEXCOORD2,
					float3 lightDirT : TEXCOORD3) : COLOR
{
	// ------------ Calculate Pixel Normal --------------
	// Normalize
	toEyeT = normalize( toEyeT );
	lightDirT = normalize( lightDirT );

	// Light vector is opposite the direction of the light
	float3 lightVecT = -lightDirT;

	// Sample the normal map
	float3 nor = float3(1.0, 0.0, 1.0);
	if(useNormal == 1) nor = tex2D(NormalMapSampler, tex);
	//float3 nor = tex2D(NormalMapSampler, tex);

	// Convert from compressed to true interval (0-1 -> -1-1)
	nor = (2.0f * nor) - 1.0f;
	
	// Normalize to make it a unit vector
	nor = -1.0 * normalize( nor );

	//------ Calculate Diffuse Color ----------//
	// zero out the start component
	float4 diffuseComponent = (float4)0.0f;

	// calculate the normals on a pixel level and get diffuse color
	float4 diffCoeff = (float4)0;
	float s = max(dot(nor,lightVecT), 0.0f);
	diffCoeff.rgb = (s*gLightColor).rgb;
	diffCoeff.a = 1.0f;

	// get diffuse color from texture
	float4 textureColor = (float4)1.0;
	if(useTexture == 1) textureColor = tex2D(s_2D, tex);

	// calculate material color
	float4 diffuseMaterialColor = textureColor * gDiffuseMtrl;

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

	// get and normalize the viewer vector
	float3 v = normalize(gViewerPos - posW);

	// calculate the spec reflection vector
	float3 r = reflect(-lightVecT, nor);

	// determine how much spec light gets to the viewer's eye
	float t = pow(max(dot(v, r), 0.0f), gSpecularPower);

	// kill spec if diffuse is low
	if(s <= 0.0f)
	     t = 0.0f;

	// get the combined material color
	float4 specularMaterialColor = gSpecularMtrl;

	// combine the material and light color with the specular power (t)
	specularComponent = t * gLightColor * specularMaterialColor;

	//--------Calculate Final Color--------//
	float4 finalColor = (diffuseComponent * gDiffuseCoefficient) +  // diffuse
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

