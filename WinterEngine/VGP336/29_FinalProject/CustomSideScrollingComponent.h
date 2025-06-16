#pragma once

#include "CustomTypeIds.h"

class CustomSideScrollingComponent : public WinterEngine::Component
{
public:
	SET_TYPE_ID(CustomComponentId::CustomSideScrollingComponent);

	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Deserialize(const rapidjson::Value& value) override;

private:
	WinterEngine::TransformComponent* mTransformComponent = nullptr;
	float mScrollSpeed = 0.0f;
};