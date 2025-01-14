#include "GameState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Input;

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

	Mesh ball = MeshBuilder::CreateSphere(60, 60, 0.5f);
	mBall.meshBuffer.Initialize(ball);
	mBall.diffuseMapId = TextureCache::Get()->LoadTexture("misc/basketball.jpg");

	Mesh ground = MeshBuilder::CreateGroundPlane(10, 10, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureCache::Get()->LoadTexture("misc/concrete.jpg");

	mAnimationTime = 0.0f;

	mAnimation = AnimationBuilder()
		.AddPositionKey({ -0.5f, 1.5f, 0.0f }, 0.0f)
		.AddPositionKey({ 0.0f, 0.5f, 0.0f }, 0.3f)
		.AddPositionKey({ 0.5f, 1.5f, 0.0f }, 1.0f)
		.AddPositionKey({0.0f, 0.5f, 0.0f}, 1.3f)
		.AddPositionKey({-0.5f, 1.5f, 0.0f}, 2.0f)
		.AddScaleKey({1.0f, 1.0f, 1.0f}, 0.25f)
		.AddScaleKey({1.0f, 0.5f, 1.0f}, 0.3f)
		.AddScaleKey({1.0f, 1.0f, 1.0f}, 0.35f)		
		.AddScaleKey({1.0f, 1.0f, 1.0f}, 1.25f)
		.AddScaleKey({1.0f, 0.5f, 1.0f}, 1.3f)
		.AddScaleKey({1.0f, 1.0f, 1.0f}, 1.35f)
		.AddRotationKey(Quaternion::Identity, 0.0f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 90.0f * Math::Constants::DegToRad), 0.5f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 180.0f * Math::Constants::DegToRad), 1.0f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 270.0f * Math::Constants::DegToRad), 1.5f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 360.0f * Math::Constants::DegToRad), 2.0f)
		.Build();
}
void GameState::Terminate()
{
	mGround.Terminate();
	mBall.Terminate();
	mStandardEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
	if (mAnimation.GetDuration() > 0.0f)
	{
		mAnimationTime += deltaTime;
		while (mAnimationTime > mAnimation.GetDuration())
		{
			mAnimationTime -= mAnimation.GetDuration();
		}
	}


	auto input = Input::InputSystem::Get();
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
}
void GameState::Render()
{
	mBall.transform = mAnimation.GetTransform(mAnimationTime);
	mStandardEffect.Begin();
		mStandardEffect.Render(mGround);
		mStandardEffect.Render(mBall);
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
	ImGui::End();
}