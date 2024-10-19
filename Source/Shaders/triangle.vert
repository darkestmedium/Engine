// We will be using glsl version 4.5 syntax.
#version 450


// Grid position are in xy clipped space
vec3 gridPlane[6] = vec3[](
	vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
	vec3(-1, -1, 0), vec3(1, 1, 0), vec3(1, -1, 0)
);

void main() 
{
	// Output the position of each vertex.
	gl_Position = vec4(gridPlane[gl_VertexIndex], 1.0f);
}