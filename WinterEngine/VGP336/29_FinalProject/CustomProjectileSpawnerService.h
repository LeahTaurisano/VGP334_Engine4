#pragma once

#include "CustomTypeIds.h"

class CustomDebugDrawComponent;

class CustomDebugDrawService : public WinterEngine::Service
{
public:
	SET_TYPE_ID(CustomServiceId::CustomProjectileSpawnerService);

	void Update(float deltaTime) override;

private:
	using HazardProjectilePool = std::vector<CustomDebugDrawComponent*>;
	using PointProjectilePool = std::vector<CustomDebugDrawComponent*>;
	float mTimer = 0.0f;
};