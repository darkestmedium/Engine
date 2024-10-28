// We will be using glsl version 4.5 syntax.
#version 460

// Push constants block.
layout(push_constant) uniform ViewUniforms
{
	mat4 view;
	mat4 proj;
	mat4 viewproj;
	vec3 pos;
	vec3 nearPoint;
	vec3 farPoint;
} view;


layout(set = 0, binding = 0) uniform  CameraBuffer
{
	mat4 view;
	mat4 proj;
	mat4 viewproj;
	vec3 pos;
	vec3 nearPoint;
	vec3 farPoint;
} cameraData;


// layout(location = 1) out vec3 nearPoint;
// layout(location = 2) out vec3 farPoint;


// Grid position are in xy clipped space.
vec3 gridPlane[6] = vec3[](
	vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
	vec3(-1, -1, 0), vec3(1, 1, 0), vec3(1, -1, 0)
);



vec3 UnprojectPoint(float x, float y, float z, mat4 view, mat4 projection)
{
	mat4 viewInv = inverse(view);
	mat4 projInv = inverse(projection);
	vec4 unprojectedPoint =  viewInv * projInv * vec4(x, y, z, 1.0);

	return unprojectedPoint.xyz / unprojectedPoint.w;
}


void main() 
{
	// vec3 p = gridPlane[gl_VertexIndex].xyz;
	// vec3 near = view.nearPoint;
	// vec3 far = view.farPoint;

	// near = UnprojectPoint(p.x, p.y, 0.0, view.view, view.proj).xyz; // unprojecting on the near plane
	// far = UnprojectPoint(p.x, p.y, 1.0, view.view, view.proj).xyz; // unprojecting on the far plane
	// gl_Position = vec4(p, 1.0); // using directly the clipped coordinates

	gl_Position = view.proj * view.view * vec4(gridPlane[gl_VertexIndex].xyz, 1.0);
}