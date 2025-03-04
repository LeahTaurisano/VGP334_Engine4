#include "GameState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Input;
using namespace WinterEngine::Audio;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 2.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 1.0f, 0.0f });

	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	Mesh ground = MeshBuilder::CreateGroundPlane(30, 30, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureCache::Get()->LoadTexture("misc/concrete.jpg");
	mGroundShape.InitializeHull({ 15.0f, 0.5f, 15.0f }, { 0.0f, -0.5, 0.0f });
	mGroundRB.Initialize(mGround.transform, mGroundShape);

	mOrbRadius = 1.0f;
	Mesh orb = MeshBuilder::CreateSphere(10, 10, mOrbRadius);
	mOrb.meshBuffer.Initialize(orb);
	mOrb.diffuseMapId = TextureCache::Get()->LoadTexture("Sprites/blue.jpg");
	float randX = rand() % 30;
	float randZ = rand() % 30;
	mOrb.transform.position = { randX - 15, 1.0f, randZ - 15 };

	numSegments = 20;
	activeSegments = 1;
	float maxSphereSize = 1.0f;
	float minSphereSize = 0.25f;
	for (uint32_t i = 0; i < numSegments; ++i)
	{
		const float t = static_cast<float>(i) / static_cast<float>(numSegments - 1);
		float sphereSize = Math::Lerp(maxSphereSize, minSphereSize, t);
		Mesh sphere = MeshBuilder::CreateSphere(30, 30, sphereSize);
		BodyPart& newPart = mBodyParts.emplace_back();
		newPart.segment.meshBuffer.Initialize(sphere);
		newPart.segment.diffuseMapId = TextureCache::Get()->LoadTexture("Sprites/green.jpg");
		newPart.range = sphereSize;
		newPart.isActive = static_cast<int>(i) < activeSegments ? true : false;
			
	}

	mBodyAnchorShape.InitializeSphere(maxSphereSize);
	mBodyAnchorRB.Initialize(mBodyParts[0].segment.transform, mBodyAnchorShape, 1.0f);
}
void GameState::Terminate()
{
	for (auto& part : mBodyParts)
	{
		part.segment.Terminate();
	}
	mBodyAnchorRB.Terminate();
	mBodyAnchorShape.Terminate();
	mOrb.Terminate();
	mGroundRB.Terminate();
	mGroundShape.Terminate();
	mGround.Terminate();
	mStandardEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
	InputSystem* input = InputSystem::Get();
	const float speed = 5.0f;
	Vector3 velocity = Vector3::Zero;
	if (input->IsKeyDown(KeyCode::UP))
	{
		velocity.z = 1.0f;
	}	
	else if (input->IsKeyDown(KeyCode::DOWN))
	{
		velocity.z = -1.0f;
	}
	if (input->IsKeyDown(KeyCode::RIGHT))
	{
		velocity.x = 1.0f;
	}	
	else if (input->IsKeyDown(KeyCode::LEFT))
	{
		velocity.x = -1.0f;
	}
	if (MagnitudeSqr(velocity) > 0.0f)
	{
		velocity = Normalize(velocity) * speed;
	}
	velocity.y = mBodyAnchorRB.GetVelocity().y;
	if (input->IsKeyPressed(KeyCode::SPACE))
	{
		velocity.y = 10.0f;
	}
	mBodyAnchorRB.SetVelocity(velocity);

	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	if (MagnitudeSqr(mOrb.transform.position - mBodyParts[0].segment.transform.position) < (mOrbRadius + mBodyParts[0].range) * (mOrbRadius + mBodyParts[0].range))
	{
		float randX = rand() % 30;
		float randZ = rand() % 30;
		mOrb.transform.position = { randX - 15, 1.0f, randZ - 15 };
		++activeSegments;
		UpdateActiveSegments();
	}
}

void GameState::Render()
{
	for (size_t i = 1; i < mBodyParts.size(); ++i)
	{
		BodyPart& part = mBodyParts[i];
		if (part.isActive)
		{
			BodyPart& prevPart = mBodyParts[i - 1];
			Vector3 dir = part.segment.transform.position - prevPart.segment.transform.position;
			if (MagnitudeSqr(dir) > 0)
			{
				dir = Normalize(dir);
			}
			else
			{
				dir = Vector3::ZAxis;
			}
			part.segment.transform.position = prevPart.segment.transform.position + (dir * prevPart.range);
		}
	}

	mStandardEffect.Begin();
		for (auto& part : mBodyParts)
		{
			if (part.isActive)
			{
				mStandardEffect.Render(part.segment);
			}
		}
		mStandardEffect.Render(mOrb);
		mStandardEffect.Render(mGround);
	mStandardEffect.End();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.1f))
		{
			mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
		}

		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}
	if (ImGui::CollapsingHeader("Segments", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragInt("Count", &activeSegments, 1, 1, numSegments))
		{
			UpdateActiveSegments();
		}
	}
	ImGui::End();
}

void GameState::UpdateActiveSegments()
{
	for (int i = 1; i < numSegments; ++i)
	{
		if (i < activeSegments)
		{
			mBodyParts[i].isActive = true;
		}
		else
		{
			mBodyParts[i].isActive = false;
		}
	}
}

