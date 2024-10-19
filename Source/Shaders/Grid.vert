// We will be using glsl version 4.5 syntax.
#version 450

// Push constants block.
layout(push_constant) uniform constants
{
	mat4 view;
	mat4 proj;
	vec3 pos;
} view;

// Grid position are in xy clipped space.
vec3 gridPlane[6] = vec3[](
	vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
	vec3(-1, -1, 0), vec3(1, 1, 0), vec3(1, -1, 0)
);


void main() 
{
	// Output the position of each vertex.

	gl_Position = view.proj * view.view * vec4(gridPlane[gl_VertexIndex].xyz, 1.0);
}