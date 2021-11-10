#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;
layout(location = 2) in vec2 vertex_texel;

// Output data ; will be interpolated for each fragment.
out vec2 texel;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;

// Values that stay constant for the whole mesh.
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 LightPosition_worldspace;

void main()
{
	gl_Position = projection * view * model * vec4(vertexPosition_modelspace, 1.0);
	Position_worldspace = (model * vec4(vertexPosition_modelspace, 1.0)).xyz;
	Normal_cameraspace = vec3(vertexNormal_modelspace);
	texel = vertex_texel;
}
