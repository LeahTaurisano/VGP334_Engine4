#include "CustomProjectileSpawnerService.h"
#include "CustomProjectileComponent.h"

void CustomProjectileSpawnerService::Register(CustomProjectileComponent* projectileComponent)
{
	if (projectileComponent->IsHazard())
	{
		auto iter = std::find(mHazardProjectilePool.begin(), mHazardProjectilePool.end(), projectileComponent);
		if (iter == mHazardProjectilePool.end())
		{
			mHazardProjectilePool.push_back(projectileComponent);
		}
	}
	else
	{
		auto iter = std::find(mPointProjectilePool.begin(), mPointProjectilePool.end(), projectileComponent);
		if (iter == mPointProjectilePool.end())
		{
			mPointProjectilePool.push_back(projectileComponent);
		}
	}
}

void CustomProjectileSpawnerService::Unregister(CustomProjectileComponent* projectileComponent)
{
	if (projectileComponent->IsHazard())
	{
		auto iter = std::find(mHazardProjectilePool.begin(), mHazardProjectilePool.end(), projectileComponent);
		if (iter != mHazardProjectilePool.end())
		{
			mHazardProjectilePool.erase(iter);
		}
	}
	else
	{
		auto iter = std::find(mPointProjectilePool.begin(), mPointProjectilePool.end(), projectileComponent);
		if (iter == mPointProjectilePool.end())
		{
			mPointProjectilePool.erase(iter);
		}
	}
}

void CustomProjectileSpawnerService::Update(float deltaTime)
{
	mTimer += deltaTime;
	if (mTimer > 2.0f)
	{
		int randDir = rand() % 3;
		mHazardProjectilePool[mHazardNext % mHazardProjectilePool.size()]->FireProjectile(randDir);
		mHazardProjectilePool[mHazardReset % mHazardProjectilePool.size()]->ResetProjectile();
		++mHazardNext;
		++mHazardReset;
		mTimer = 0.0f;
	}
}
