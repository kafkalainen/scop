#version 330 core

struct Material
{
	sampler2D	texture_diffuse1;
	sampler2D	texture_specular1;
	float		texture_shininess1;
};

struct Light
{
	vec3		position;
	vec3		ambient;
	vec3		diffuse;
	vec3		specular;
};

in vec2			texel;
in vec3			Position_worldspace;
in vec3			Normal_cameraspace;

out vec4 color;

uniform				Light light;
uniform				Material material;
uniform vec3		viewPos;

void main()
{
	vec3 ambient_colour = texture(material.texture_diffuse1, texel).rgb * light.ambient;
	vec3 normal = normalize(Normal_cameraspace);
	vec3 lightDir = normalize(light.position - Position_worldspace);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse_colour = diff * texture(material.texture_diffuse1, texel).rgb * light.diffuse;
	vec3 view_dir = normalize(viewPos - Position_worldspace);
	vec3 reflect_dir = reflect(-lightDir, normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.texture_shininess1);
	vec3 specular_colour = spec * texture(material.texture_diffuse1, texel).rgb * light.specular;
	color.rgb = ambient_colour + diffuse_colour + specular_colour;
	color.a = 1.0;
}
