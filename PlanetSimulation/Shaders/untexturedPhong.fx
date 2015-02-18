// FX Parameters

// transforms
uniform extern float4x4 gWorld;
uniform extern float4x4 gWVP;
uniform extern float4x4 gWorldInverseTranspose;

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

// Structure
struct OutputVS
{
	float4 posH    : POSITION0;
	float3 posW	   : TEXCOORD1;
	float2 uvH     : TEXCOORD0;
	float3 normalH : NORMAL0;
};

// Vertex Shader
OutputVS PhongVS( float3 posL : POSITION0, float2 uvL : TEXCOORD0, float3 normalL : NORMAL0 )
{
	// Zero out our output
	OutputVS outVS = (OutputVS)0;

	// Transform the normal to world space
	float3 normalW = mul(float4(normalL, 0.0f), gWorldInverseTranspose).xyz;
	normalW = normalize(normalW);
	outVS.normalH = normalW;

	// calculate world position of vertex
	outVS.posW = mul(float4(posL, 1.0f), gWorld).xyz;

	// Transform position to homogenous clip space
	outVS.posH = mul(float4(posL,1.0), gWVP);

	// write out the UV coords
	outVS.uvH = uvL;

	// Done--return the output
	return outVS;
}

// Pixel Shader
float4 PhongPS( float2 tex : TEXCOORD0, float3 nor : NORMAL0, float3 posW : TEXCOORD1 ) : COLOR
{
	//------ Calculate Diffuse Color ----------//
	// zero out the start component
	float4 diffuseComponent = (float4)0.0f;

	// calculate the normals on a pixel level and get diffuse color
	float4 diffCoeff = (float4)0;
	nor = normalize(nor);
	float s = max(dot(nor,gLightVecW), 0.0f);
	diffCoeff.rgb = (s*gLightColor).rgb;
	diffCoeff.a = 1.0f;

	// get final diffuse
	diffuseComponent = diffCoeff * gDiffuseMtrl;

	//-------Calculate Ambient Color--------//
	// zero out the start component
	float4 ambientComponent = (float4)0.0f;

	// combine the ambient material color with the ambient light color
	ambientComponent = gAmbientMtrl * gLightColor;

	//-------Calculate Specular Color-------//
	// zero out the start component
	float4 specularComponent = (float4)0.0f;

	// get and normalize the viewer vector
	float3 v = normalize(gViewerPos - posW);

	// calculate the spec reflection vector
	float3 r = reflect(-gLightVecW, nor);

	// determine how much spec light gets to the viewer's eye
	float t = pow(max(dot(v, r), 0.0f), gSpecularPower);

	// combine the material and light color with the specular power (t)
	specularComponent = t * gLightColor * gSpecularMtrl;

	//--------Calculate Final Color--------//
	float4 finalColor = (diffuseComponent * gDiffuseCoefficient) +  // diffuse
						(ambientComponent * gAmbientCoefficient) +  // ambient
						(specularComponent * gSpecularCoefficient); // specular

	return finalColor;
}

technique PhongTech
{
	pass P0
	{
		// specify the vertex and pixel shader associated with this pass
		vertexShader = compile vs_3_0 PhongVS();
		pixelShader  = compile ps_3_0 PhongPS();

		FillMode = Solid;
	}

	pass P1
	{
		// specify the vertex and pixel shader associated with this pass
		vertexShader = compile vs_3_0 PhongVS();
		pixelShader  = compile ps_3_0 PhongPS();

		FillMode = Wireframe;
	}
}
