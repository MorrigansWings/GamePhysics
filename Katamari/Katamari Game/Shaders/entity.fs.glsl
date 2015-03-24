#version 430 core

uniform sampler2D uTexDiffuse;

uniform vec3  uGlobalAmbient;
uniform vec3  uLightColor;
uniform vec3  uLightDirection;
uniform vec3  uHalfVector;
uniform float uShininess;
uniform float uStrength;
uniform bool  uHasGlobalLight;

in vec4 vColor;
in vec3 vNormal;
in vec2 vTexCoord;

layout (location = 0) out vec4 oFragColor;

void main()
{	
	vec2 texCoord = vTexCoord;
	texCoord.y = 1.0f - vTexCoord.y;

	if ( ! uHasGlobalLight)
	{
		oFragColor = texture(uTexDiffuse, texCoord);
		return;
	}

	float diffuse = max(0.0, dot(vNormal, uLightDirection));
	float specular = max(0.0, dot(vNormal, uHalfVector));
		
	if (diffuse == 0.0f)
		specular = 0.0f;
	else
		specular = pow(specular, uShininess);

	vec3 scatteredLight = uGlobalAmbient + uLightColor * diffuse;
	vec3 reflectedLight = uLightColor * specular * uStrength;

	vec4 color = texture(uTexDiffuse, texCoord);

	oFragColor.rgb = min(scatteredLight * color.rgb, vec3(1.0f));
	oFragColor.a = color.a;
}