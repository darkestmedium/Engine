#pragma once

#include "vk_types.h"


class Transform
{
public:
  glm::vec3 position;

  Transform()
		: position(0.0f, 0.0f, 1.0f)
	{};

	void Reset(void) {position = {0.0f, 0.0f, 0.0f};};

};

