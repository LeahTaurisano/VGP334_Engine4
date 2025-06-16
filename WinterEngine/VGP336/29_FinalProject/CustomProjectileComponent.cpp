#include "CustomProjectileComponent.h"
#include "CustomProjectileSpawnerService.h"

using namespace WinterEngine;

void CustomProjectileComponent::Initialize()
{
	mRigidBodyComponent = GetOwner().GetComponent<RigidBodyComponent>();
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	CustomProjectileSpawnerService* cdds = GetOwner().GetWorld().GetService<CustomProjectileSpawnerService>();
	cdds->Register(this);
}

void CustomProjectileComponent::Terminate()
{
	mRigidBodyComponent = nullptr;
	CustomProjectileSpawnerService* cdds = GetOwner().GetWorld().GetService<CustomProjectileSpawnerService>();
	cdds->Unregister(this);
}

void CustomProjectileComponent::Deserialize(const rapidjson::Value& value)
{
	SaveUtil::ReadBool("IsHazard", isHazard, value);
}

void CustomProjectileComponent::Update(float deltaTime)
{
	if (isActive)
	{
		mRigidBodyComponent->SetPosition({ mTransformComponent->position.x + mDirection.x * deltaTime, 
										   mTransformComponent->position.y + mDirection.y * deltaTime,
										   mTransformComponent->position.z + mDirection.z * deltaTime 
		});
	}
}

bool CustomProjectileComponent::IsHazard()
{
	return isHazard;
}

void CustomProjectileComponent::ResetProjectile()
{
	mRigidBodyComponent->SetPosition({ 0.0f, -10.0f, -10.0f }); //offscreen
	mRigidBodyComponent->SetVelocity(Math::Vector3::Zero);
	mDirection = Math::Vector3::Zero;
	isActive = false;
}

void CustomProjectileComponent::FireProjectile(int dir)
{
	isActive = true;
	float randomPos = 0.0f;
	switch (dir)
	{
	case 0: //TOP
		randomPos = (rand() % 10) - 5;
		mRigidBodyComponent->SetPosition({randomPos, 10.0f, 0.0f});
		//mRigidBodyComponent->SetVelocity({-randomPos / 2, -1.0f, 0.0f});
		mDirection = { -randomPos / 2, -1.0f, 0.0f };
		break;
	case 1: //LEFT
		randomPos = rand() % 30;
		mRigidBodyComponent->SetPosition({ -5.0f, randomPos, 0.0f });
		//mRigidBodyComponent->SetVelocity({ 1.0f, -randomPos / 2, 0.0f });
		mDirection = { 1.0f, -randomPos / 2, 0.0f };
		break;
	case 2: //RIGHT
		randomPos = rand() % 30;
		mRigidBodyComponent->SetPosition({ 5.0f, randomPos, 0.0f });
		//mRigidBodyComponent->SetVelocity({ -1.0f, -randomPos / 2, 0.0f });
		mDirection = { -1.0f, -randomPos / 2, 0.0f };
		break;
	default:
		ResetProjectile();
		break;
	}
}
