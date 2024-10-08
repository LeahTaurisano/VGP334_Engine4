#include "GameState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	Mesh mesh = MeshBuilder::CreateSphere(30, 30, 1.0f);
	float xPos = 1.0f;
	for (int i = 0; i < 9; ++i)
	{
		RenderObject& planet = mPlanets.emplace_back();
		planet.meshBuffer.Initialize(mesh);
		planet.diffuseTextureId = TextureCache::Get()->LoadTexture("planets/earth/earth.jpg");
		planet.transform.position.x = xPos;
		++xPos;
	}

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);

}
void GameState::Terminate()
{
	mStandardEffect.Terminate();
	for (RenderObject& planet : mPlanets)
	{
		planet.Terminate();
	}
}

void GameState::Update(float deltaTime)
{
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
	mStandardEffect.Begin();
	for (RenderObject& planet : mPlanets)
	{
		mStandardEffect.Render(planet);
	}
	mStandardEffect.End();
}

void GameState::DebugUI()
{
	
}