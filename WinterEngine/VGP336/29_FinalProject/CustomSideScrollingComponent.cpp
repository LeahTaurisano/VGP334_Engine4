#include "CustomSideScrollingComponent.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Math;

void CustomSideScrollingComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
}

void CustomSideScrollingComponent::Terminate()
{
	mTransformComponent = nullptr;
}

void CustomSideScrollingComponent::Update(float deltaTime)
{
	mTransformComponent->position.x -= mScrollSpeed * deltaTime;
}

void CustomSideScrollingComponent::Deserialize(const rapidjson::Value& value)
{
	SaveUtil::ReadFloat("ScrollSpeed", mScrollSpeed, value);
}
