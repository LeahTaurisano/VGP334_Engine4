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
	using TerrainBlocks = std::vector<WinterEngine::GameObject*>;
	TerrainBlocks mTerrainBlocks;
	using TerrainRBComps = std::vector<WinterEngine::RigidBodyComponent*>;
	TerrainRBComps mTerrainRBComps;
	float mScrollSpeed = 0.0f;
	float mTimer = 0.0f;

	enum class Stages
	{
		STAGE_1,
		STAGE_2,
		STAGE_3,
		TRANSITION
	};
	Stages mCurrentStage = Stages::STAGE_1;
};