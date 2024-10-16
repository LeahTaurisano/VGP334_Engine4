#pragma once

#include "Colors.h"

namespace WinterEngine::Graphics
{
	struct DirectionalLight
	{
		Color ambient = Colors::White;  // light color without contact
		Color diffuse = Colors::White;  // base light color
		Color specular = Colors::White; // highlight color
		Math::Vector3 direction = Math::Vector3::ZAxis;
		float padding = 0.0f;
	};
}