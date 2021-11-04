#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

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
uniform Material material;

void main()
{
	float	distance = length(LightPosition_worldspace - Position_worldspace);
	vec3	object_colour = mix(texture(texture1, UV), texture(texture2, UV), 0.2f).rgb;
	vec3	ambient_light = material.ambient * LightColor;

	vec3	normal = normalize(Normal_cameraspace);
	vec3	lightDir = normalize(LightDirection_cameraspace);
	float	diff = max(dot(normal, lightDir), 0.0);
	vec3	diffuse_light = (diff * material.diffuse) * LightColor;

	vec3	view_dir = normalize(EyeDirection_cameraspace);
	vec3	reflect_dir = reflect(-lightDir, normal);
	float	spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
	vec3	specular_light = (spec * material.specular) * LightColor;
	color.a = 0.3;
	color.rgb = (ambient_light + diffuse_light + specular_light) * object_colour;
}
