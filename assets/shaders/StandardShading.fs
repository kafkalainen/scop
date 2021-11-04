#version 330 core

in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

out vec4 color;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform mat4 MV;
uniform vec3 LightPosition_worldspace;
uniform vec3 LightColor;
uniform float LightPower;

void main()
{
	vec3 MaterialDiffuseColor = mix(texture(texture1, UV), texture(texture2, UV), 0.2f).rgb;
	vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);
	float distance = length(LightPosition_worldspace - Position_worldspace);
	vec3 normal = normalize(Normal_cameraspace);
	vec3 lightDir = normalize(LightDirection_cameraspace);
	float cosTheta = clamp(dot(normal, lightDir), 0, 1);
	vec3 view_dir = normalize(EyeDirection_cameraspace);
	vec3 reflect_dir = reflect(-lightDir, normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
	color.a = 0.3;
	color.rgb =
		MaterialAmbientColor +
		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance * distance) +
		MaterialSpecularColor * LightColor * LightPower * spec / (distance * distance);
}
