#include "Camera.h"




glm::mat4 Camera::getViewMatrix() const
{
	// to create a correct model view, we need to move the world in opposite
	// direction to the camera
	//  so we will create the camera model matrix and invert
	glm::mat4 cameraTranslation = glm::translate(glm::mat4(1.f), position);
	glm::mat4 cameraRotation = getRotationMatrix();
	return glm::inverse(cameraTranslation * cameraRotation);
}


glm::mat4 Camera::getRotationMatrix() const
{
	// fairly typical FPS style camera. we join the pitch and yaw rotations into
	// the final rotation matrix

	glm::quat pitchRotation = glm::angleAxis(pitch, glm::vec3 { 1.f, 0.f, 0.f });
	glm::quat yawRotation = glm::angleAxis(yaw, glm::vec3 { 0.f, -1.f, 0.f });

	return glm::toMat4(yawRotation) * glm::toMat4(pitchRotation);
}


void Camera::processSDLEvent(SDL_Event& event)
{
	static bool isLMBPressed = false;
	static bool isRMBPressed = false;

	if (event.type == SDL_EVENT_KEY_DOWN)
	{
		if (event.key.key == SDLK_W) {velocity.z = -1;}
		if (event.key.key == SDLK_S) {velocity.z = 1;}
		if (event.key.key == SDLK_A) {velocity.x = -1;}
		if (event.key.key == SDLK_D) {velocity.x = 1;}
	}

	if (event.type == SDL_EVENT_KEY_UP)
	{
		if (event.key.key == SDLK_W) {velocity.z = 0;}
		if (event.key.key == SDLK_S) {velocity.z = 0;}
		if (event.key.key == SDLK_A) {velocity.x = 0;}
		if (event.key.key == SDLK_D) {velocity.x = 0;}
	}

	// Check for LMB press and release
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		isLMBPressed = true;
	}

	if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT)
	{
		isLMBPressed = false;
		// velocity.x = 0;
		// velocity.y = 0;
		// velocity.z = 0;
	}

	// Check for RMB press and release
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_RIGHT)
	{
		isRMBPressed = true;
	}

	if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_RIGHT)
	{
		isRMBPressed = false;
		// velocity.x = 0;
		// velocity.y = 0;
		// velocity.z = 0;
	}

	// if (event.type == SDL_EVENT_MOUSE_MOTION && isLMBPressed && !isRMBPressed)
	// {
	// 	yaw += (float)event.motion.xrel / 250.f;
	// }

	if (event.type == SDL_EVENT_MOUSE_MOTION && isRMBPressed && !isLMBPressed)
	{
		yaw += (float)event.motion.xrel / 250.f;
		pitch -= (float)event.motion.yrel / 250.f;
	}


	if (event.type == SDL_EVENT_MOUSE_MOTION && isLMBPressed && isRMBPressed)
	{
		velocity.x = (float)event.motion.xrel / 25.f;
		velocity.y = -(float)event.motion.yrel / 25.f;
	// 	if (event.motion.xrel != 0)
	// 	{
	// 		velocity.x = (float)event.motion.xrel / 25.f;
	// 	}
	// 	else
	// 	{
	// 		velocity.x = 0;
	// 		velocity.y = 0;
	// 		velocity.z = 0;
	// 	}

	// 	if (event.motion.yrel != 0)
	// 	{
	// 		velocity.y = -(float)event.motion.yrel / 25.f;
	// 	}
	// 	else
	// 	{
	// 		velocity.x = 0;
	// 		velocity.y = 0;
	// 		velocity.z = 0;

	// 	}
	}

}


void Camera::update()
{
	glm::mat4 cameraRotation = getRotationMatrix();
	position += glm::vec3(cameraRotation * glm::vec4(velocity * 0.5f, 0.f));
}
