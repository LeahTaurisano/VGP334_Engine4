#pragma once

#include "CustomTypeIds.h"

class CustomProjectileComponent : public WinterEngine::Component
{
public:
	SET_TYPE_ID(CustomComponentId::CustomProjectileComponent);

	void Initialize() override;
	void Terminate() override;
	void Deserialize(const rapidjson::Value& value) override;
	void Update(float deltaTime) override;

	bool IsHazard();
	void ResetProjectile();
	void FireProjectile(int dir);

private:
	WinterEngine::RigidBodyComponent* mRigidBodyComponent = nullptr;
	WinterEngine::TransformComponent* mTransformComponent = nullptr;
	bool isHazard = true;
	bool isActive = false;
	WinterEngine::Math::Vector3 mDirection = WinterEngine::Math::Vector3::Zero;
};