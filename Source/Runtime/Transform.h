#pragma once

#include "vk_types.h"


class Transform
{
public:

  Transform()
		: position(0.0f, 0.0f, 0.0f)
	{};

  glm::vec3 position;

	void Reset(void) {position = {0.0f, 0.0f, 0.0f};};

};

