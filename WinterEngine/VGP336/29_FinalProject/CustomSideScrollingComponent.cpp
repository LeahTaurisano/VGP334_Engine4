#include "CustomSideScrollingComponent.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Math;

void CustomSideScrollingComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mTerrainBlocks = GetOwner().GetChildren();

	for (int i = 0; i < mTerrainBlocks.size(); ++i)
	{
		RigidBodyComponent* rb = mTerrainBlocks[i]->GetComponent<RigidBodyComponent>();
		mTerrainRBComps.push_back(rb);
	}
}

void CustomSideScrollingComponent::Terminate()
{
	mTransformComponent = nullptr;
}

void CustomSideScrollingComponent::Update(float deltaTime)
{
	mTimer += deltaTime;
	if (mTimer > 10.0f && mTimer < 20.0f)
	{
		mCurrentStage = Stages::TRANSITION;
	}	
	else if (mTimer > 20.0f && mTimer < 30.0f)
	{
		mCurrentStage = Stages::STAGE_2;
	}	
	else if (mTimer > 30.0f && mTimer < 40.0f)
	{
		mCurrentStage = Stages::TRANSITION;
	}
	else if (mTimer > 40.0f && mTimer < 50.0f)
	{
		mCurrentStage = Stages::STAGE_3;
	}

	if (mCurrentStage == Stages::TRANSITION)
	{
		for (int i = 0; i < mTerrainRBComps.size(); ++i)
		{
			TransformComponent* tf = mTerrainBlocks[i]->GetComponent<TransformComponent>();
			mTerrainRBComps[i]->SetPosition({ tf->position.x - mScrollSpeed * deltaTime, tf->position.y, tf->position.z });
		}
	}
}

void CustomSideScrollingComponent::Deserialize(const rapidjson::Value& value)
{
	SaveUtil::ReadFloat("ScrollSpeed", mScrollSpeed, value);
}
