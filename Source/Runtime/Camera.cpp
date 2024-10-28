#include "Camera.h"


const char *Camera::GetName() const
{
	return "Camera";
}


glm::mat4 Camera::GetViewMatrix() const
{
	// to create a correct model view, we need to move the world in opposite
	// direction to the camera
	//  so we will create the camera model matrix and invert
	glm::mat4 cameraTranslation = glm::translate(glm::mat4(1.f), mPosition);
	glm::mat4 cameraRotation = GetRotationMatrix();
	return glm::inverse(cameraTranslation * cameraRotation);
}

glm::mat4 Camera::GetRotationMatrix() const
{
	// fairly typical FPS style camera. we join the pitch and yaw rotations into
	// the final rotation matrix

	glm::quat pitchRotation = glm::angleAxis(mPitch, glm::vec3 { 1.f, 0.f, 0.f });
	glm::quat yawRotation = glm::angleAxis(mYaw, glm::vec3 { 0.f, -1.f, 0.f });

	return glm::toMat4(yawRotation) * glm::toMat4(pitchRotation);
}

glm::vec3 Camera::GetPosition() const
{
	return mPosition;
}

glm::vec3 Camera::GetVeloctiy() const
{
	return mVelocity;
}

float Camera::GetPitch() const
{
	return mPitch;
}

float Camera::GetYaw() const
{
	return mYaw;
}

float Camera::GetNearClip() const
{
	return mNearClip;
}

float Camera::GetFarClip() const
{
	return mFarClip;
}


void Camera::ProcessSDLEvent(SDL_Event& event)
{
	static bool bIsLMBPressed = false;
	static bool bIsRMBPressed = false;

	// Keyboard
	if (event.type == SDL_EVENT_KEY_DOWN)
	{
		if (event.key.key == SDLK_W) {mVelocity.z = -1;}
		if (event.key.key == SDLK_S) {mVelocity.z = 1;}
		if (event.key.key == SDLK_A) {mVelocity.x = -1;}
		if (event.key.key == SDLK_D) {mVelocity.x = 1;}
	}

	if (event.type == SDL_EVENT_KEY_UP)
	{
		if (event.key.key == SDLK_W) {mVelocity.z = 0;}
		if (event.key.key == SDLK_S) {mVelocity.z = 0;}
		if (event.key.key == SDLK_A) {mVelocity.x = 0;}
		if (event.key.key == SDLK_D) {mVelocity.x = 0;}
	}

	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)	{bIsLMBPressed = true;}
		if (event.button.button == SDL_BUTTON_RIGHT) {bIsRMBPressed = true;}
	}
	if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)	{bIsLMBPressed = false;}
		if (event.button.button == SDL_BUTTON_RIGHT) {bIsRMBPressed = false;}
		mVelocity.x = 0.0f;
		mVelocity.y = 0.0f;
		mVelocity.z = 0.0f;
	}


	if (event.type == SDL_EVENT_MOUSE_MOTION)
	{
		// Look Around
		if (bIsRMBPressed)
		{
			mYaw += (float)event.motion.xrel / 250.f;
			mPitch -= (float)event.motion.yrel / 250.f;
		}

		// Pan
		if (bIsLMBPressed && bIsRMBPressed)
		{
			mVelocity.x = (float)event.motion.xrel / 25.f;
			mVelocity.y = -(float)event.motion.yrel / 25.f;
		}
	}

}


void Camera::Update()
{
	glm::mat4 cameraRotation = GetRotationMatrix();
	mPosition += glm::vec3(cameraRotation * glm::vec4(mVelocity * 0.75f, 0.f));
	// mPosition += glm::vec3(cameraRotation * glm::vec4(mVelocity, 0.0f));
}
