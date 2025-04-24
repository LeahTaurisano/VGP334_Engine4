#pragma once

namespace WinterEngine
{
	enum class ComponentId
	{
		Invalid,	// default Value, not valid
		Transform,  // transform component for location data
		Camera,     // contains the camera for viewing
		FPSCamera,  // move the Camera with FPS controls
		Count		// last value, chain ids in custom components
	};

	enum class ServiceId
	{
		Invalid,    // default value, not valid
		Camera,     // manages the cameras in the world
		Count       // last value, chain ids in custom services
	};
}

#define SET_TYPE_ID(id)\
	static uint32_t StaticGetTypeId() { return static_cast<uint32_t>(id); }\
	uint32_t GetTypeId() const override { return StaticGetTypeId(); }