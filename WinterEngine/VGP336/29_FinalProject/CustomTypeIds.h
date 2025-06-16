#pragma once
#include <WinterEngine/Inc/WinterEngine.h>

enum class CustomComponentId
{
	CustomDebugDraw = static_cast<uint32_t>(WinterEngine::ComponentId::Count),
	CustomPlayerController,
	CustomSideScrollingComponent,
	CustomProjectileComponent
};

enum class CustomServiceId
{
	CustomDebugDrawDisplay = static_cast<uint32_t>(WinterEngine::ServiceId::Count),
	CustomProjectileSpawnerService
};