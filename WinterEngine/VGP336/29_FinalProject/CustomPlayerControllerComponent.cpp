#include "CustomPlayerControllerComponent.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Math;
using namespace WinterEngine::Input;

void CustomPlayerControllerComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mRBComponent = GetOwner().GetComponent<RigidBodyComponent>();
}

void CustomPlayerControllerComponent::Terminate()
{
	mRBComponent = nullptr;
}

void CustomPlayerControllerComponent::Update(float deltaTime)
{
	InputSystem* input = InputSystem::Get();
	
	if (input->IsKeyDown(KeyCode::RIGHT))
	{
		if (mTransformComponent->position.x > 5.0)
		{
			mRBComponent->SetPosition({ 4.9, mTransformComponent->position.y, mTransformComponent->position.z });
		}
		mRBComponent->SetPosition({ mTransformComponent->position.x + mSpeed * deltaTime, mTransformComponent->position.y, mTransformComponent->position.z });
	}
	else if (input->IsKeyDown(KeyCode::LEFT))
	{
		if (mTransformComponent->position.x < -5.0)
		{
			mRBComponent->SetPosition({ -4.9, mTransformComponent->position.y, mTransformComponent->position.z });
		}
		mRBComponent->SetPosition({ mTransformComponent->position.x - mSpeed * deltaTime, mTransformComponent->position.y, mTransformComponent->position.z });
	}
	if (input->IsKeyPressed(KeyCode::UP))
	{
		mRBComponent->SetVelocity({ 0, mJumpForce, 0 });
	}
}

void CustomPlayerControllerComponent::Deserialize(const rapidjson::Value& value)
{
	SaveUtil::ReadFloat("Speed", mSpeed, value);
	SaveUtil::ReadFloat("JumpForce", mJumpForce, value);
}
