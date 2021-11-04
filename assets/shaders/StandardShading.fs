#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;

out vec4 color;

uniform sampler2D	texture1;
uniform sampler2D	texture2;
uniform				Light light;
uniform				Material material;
uniform vec3		viewPos;

void main()
{
	float distance = length(light.position - Position_worldspace);
	vec3 object_colour = mix(texture(texture1, UV), texture(texture2, UV), 0.2f).rgb;
	vec3 ambient_light = material.ambient * light.ambient;

	vec3 normal = normalize(Normal_cameraspace);
	vec3 lightDir = normalize(light.position - Position_worldspace);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse_light = (diff * material.diffuse) * light.diffuse;

	vec3 view_dir = normalize(viewPos - Position_worldspace);
	vec3 reflect_dir = reflect(-lightDir, normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
	vec3 specular_light = (spec * material.specular) * light.specular;
	color.a = 0.3;
	color.rgb = (ambient_light + diffuse_light + specular_light) * object_colour;
}
