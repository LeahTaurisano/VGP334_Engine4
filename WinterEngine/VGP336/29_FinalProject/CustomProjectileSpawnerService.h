#pragma once

#include "CustomTypeIds.h"

class CustomProjectileComponent;

class CustomProjectileSpawnerService : public WinterEngine::Service
{
public:
	SET_TYPE_ID(CustomServiceId::CustomProjectileSpawnerService);

	void Register(CustomProjectileComponent* projectileComponent);
	void Unregister(CustomProjectileComponent* projectileComponent);
	void Update(float deltaTime) override;

private:
	using ProjectilePool = std::vector<CustomProjectileComponent*>;
	ProjectilePool mHazardProjectilePool;
	ProjectilePool mPointProjectilePool;
	float mTimer = 0.0f;
	int mHazardNext = 0;
	int mHazardReset = 1;
	int mPointNext = 0;
	int mPointReset = 1;
};