#pragma once

#include "CustomTypeIds.h"

class CustomDebugDrawComponent : public WinterEngine::Component 
{
public:
	SET_TYPE_ID(CustomComponentId::CustomDebugDraw);

	void Initialize() override;
	void Terminate() override;
	void Deserialize(const rapidjson::Value& value) override;

	void AddDebugDraw() const;

private:
	const WinterEngine::TransformComponent* mTransformComponent = nullptr;
	WinterEngine::Math::Vector3 mPosition = WinterEngine::Math::Vector3::Zero;
	WinterEngine::Color mColor = WinterEngine::Colors::White;

	uint32_t mSlices = 0;
	uint32_t mRings = 0;
	float mRadius = 0.0f;
};