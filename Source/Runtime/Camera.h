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
		: mPosition(position)
		, mVelocity(velocity)
		, mPitch(pitch)
		, mYaw(yaw)
		, mNearClip(nearClip)
		, mFarClip(farClip)
	{}

	// Destructors
	~Camera() {};
 
	// Getters
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetRotationMatrix() const;
	glm::vec3 GetPosition() const;
	glm::vec3 GetVeloctiy() const;
	float GetPitch() const;
	float GetYaw() const;

	float GetNearClip() const;
	float GetFarClip() const;

	// Processing
	void ProcessSDLEvent(SDL_Event &event);
	void Update();


private:
	glm::vec3 mPosition;
	glm::vec3 mVelocity;

 	float mPitch;  // vertical rotation
	float mYaw;	// horizontal rotation

	float mNearClip, mFarClip;
};



