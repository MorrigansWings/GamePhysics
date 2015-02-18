// FX Parameters
uniform extern float4x4 gWVP;
uniform extern float4 materialColor;
uniform extern int useTexture;
uniform extern texture matTexture;

// ------- Vertex Shader -----------

struct OutputVS {
	float4 posH    : POSITION0;
	float2 uvH     : TEXCOORD0;
};

OutputVS DefaultVS( float3 posL : POSITION0, float2 uvL : TEXCOORD0 )
{
	OutputVS outVS = (OutputVS)0;
	outVS.posH = mul(float4(posL,1.0f), gWVP);
	outVS.uvH = uvL;
	return outVS;
}

//--------- Pixel Shader -----------

sampler2D s_2D = sampler_state 
{ 
	Texture = <matTexture>;
	MinFilter = ANISOTROPIC;
	MagFilter = LINEAR; 
	MipFilter = LINEAR;
	MaxAnisotropy = 4;
	AddressU = WRAP;
	AddressV = WRAP;
};

float4 DefaultPS( float2 tex : TEXCOORD0 ) : COLOR
{
	float4 textureColor = (float4)1.0;
	if (useTexture == 1) textureColor = tex2D(s_2D, tex);
	return (materialColor * textureColor);
}

float4 WireframePS() : COLOR
{
	return (float4)0.0;
}

// ------------- Techniques -------------

technique Untextured
{
	pass P0
	{
		vertexShader = compile vs_3_0 DefaultVS();
		pixelShader =  compile ps_3_0 DefaultPS();
		FillMode = Solid;
	}

	pass P1
	{
		vertexShader = compile vs_3_0 DefaultVS();
		pixelShader =  compile ps_3_0 WireframePS();
		FillMode = Wireframe;
	}
}