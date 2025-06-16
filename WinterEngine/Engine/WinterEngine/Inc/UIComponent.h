#pragma once

#include "Component.h"

namespace WinterEngine
{
	class UIComponent : public Component
	{
	public:
		virtual void Render() = 0;
	};
}