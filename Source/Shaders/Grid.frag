//glsl version 4.5
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

// layout(location = 1) in vec3 nearPoint;
// layout(location = 2) in vec3 farPoint;
layout(location = 0) out vec4 outFragColor;


vec4 grid(vec3 fragPos3D, float scale)
{
	vec2 coord = fragPos3D.xz * scale; // use the scale variable to set the distance between the lines
	vec2 derivative = fwidth(coord);
	vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
	float line = min(grid.x, grid.y);
	float minimumz = min(derivative.y, 1);
	float minimumx = min(derivative.x, 1);
	vec4 color = vec4(0.2, 0.2, 0.2, 1.0 - min(line, 1.0));
	// z axis
	if (fragPos3D.x > -0.1 * minimumx && fragPos3D.x < 0.1 * minimumx)
	{
		color.z = 1.0;
	}
	// x axis
	if (fragPos3D.z > -0.1 * minimumz && fragPos3D.z < 0.1 * minimumz)
	{
		color.x = 1.0;
	}
	return color;
}


void main()
{
	float t = -view.nearPoint.y / (view.farPoint.y - view.nearPoint.y);
	vec3 fragPos3D = view.nearPoint + t * (view.farPoint - view.nearPoint);
	// outFragColor = grid(fragPos3D, 10) * float(t > 0);

	outFragColor = vec4(1.0, 0.0, 0.0, 1.0 * float(t > 0)); // opacity = 1 when t > 0, opacity = 0 otherwise
}