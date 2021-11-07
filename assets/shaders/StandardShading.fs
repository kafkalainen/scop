// #version 330 core

// struct Material
// {
// 	sampler2D	diffuse;
// 	sampler2D	specular;
// 	float		shininess;
// };

// struct Light
// {
// 	vec3		position;
// 	vec3		ambient;
// 	vec3		diffuse;
// 	vec3		specular;
// };

// in vec2			texel;
// in vec3			Position_worldspace;
// in vec3			Normal_cameraspace;

// out vec4 color;

// uniform				Light light;
// uniform				Material material;
// uniform vec3		viewPos;

// void main()
// {
// 	vec3 ambient_colour = texture(material.diffuse, texel).rgb * light.ambient;
// 	vec3 normal = normalize(Normal_cameraspace);
// 	vec3 lightDir = normalize(light.position - Position_worldspace);
// 	float diff = max(dot(normal, lightDir), 0.0);
// 	vec3 diffuse_colour = diff * texture(material.diffuse, texel).rgb * light.diffuse;
// 	vec3 view_dir = normalize(viewPos - Position_worldspace);
// 	vec3 reflect_dir = reflect(-lightDir, normal);
// 	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
// 	vec3 specular_colour = spec * texture(material.diffuse, texel).rgb * light.specular;
// 	color.rgb = ambient_colour + diffuse_colour + specular_colour;
// 	color.a = 1.0;
// }

#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{
	FragColor = texture(texture_diffuse1, TexCoords);
}
