#pragma once

#include "vk_types.h"
// #include "Transform.h"


#include <SDL3/SDL_events.h>



// class Camera : public Transform
class Camera
{
public:

	// Constructors
	Camera(glm::vec3 position = {0.0f, 0.0f, 0.0f}, glm::vec3 velocity = {0.0f, 0.0f, 0.0f}, float pitch = 0.0f, float yaw = 0.0f, float nearClip = 0.01f, float farClip = 1000.0f)
		: position(position)
		, velocity(velocity)
		, pitch(pitch)
		, yaw(yaw)
		, nearClip(nearClip)
		, farClip(farClip)
	{}

	// Destructors
	~Camera() {};

	glm::vec3 position;
	glm::vec3 velocity;

 	float pitch;  // vertical rotation
	float yaw;	// horizontal rotation

	float nearClip, farClip;

	glm::mat4 getViewMatrix() const;
	glm::mat4 getRotationMatrix() const;

	void processSDLEvent(SDL_Event &event);

	void update();
};



