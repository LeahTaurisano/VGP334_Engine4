#pragma once

#include "CustomTypeIds.h"

class CustomPlayerControllerComponent : public WinterEngine::Component
{
public:
	SET_TYPE_ID(CustomComponentId::CustomPlayerController);

	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Deserialize(const rapidjson::Value& value) override;

private:
	WinterEngine::TransformComponent* mTransformComponent = nullptr;
	WinterEngine::RigidBodyComponent* mRBComponent = nullptr;
	float mSpeed = 0.0f;
	float mJumpForce = 0.0f;
};