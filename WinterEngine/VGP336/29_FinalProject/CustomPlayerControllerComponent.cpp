#include "CustomPlayerControllerComponent.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Math;
using namespace WinterEngine::Input;

void CustomPlayerControllerComponent::Initialize()
{
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
		mRBComponent->SetVelocity({ mSpeed, 0, 0 });
	}
	else if (input->IsKeyDown(KeyCode::LEFT))
	{
		mRBComponent->SetVelocity({ -mSpeed, 0, 0 });
	}
	else if (input->IsKeyPressed(KeyCode::UP))
	{
		mRBComponent->SetVelocity({ 0, mJumpForce, 0 });
	}
}

void CustomPlayerControllerComponent::Deserialize(const rapidjson::Value& value)
{
	SaveUtil::ReadFloat("Speed", mSpeed, value);
	SaveUtil::ReadFloat("JumpForce", mJumpForce, value);
}
