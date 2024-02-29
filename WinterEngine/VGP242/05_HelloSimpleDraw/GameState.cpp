#include "GameState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
}
void GameState::Terminate()
{
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
	Matrix4 mat = Matrix4::Identity;
	mat._42 = 1.0f;
	/*SimpleDraw::AddLine({ 0.0f, 0.0f, 0.0f }, { 2.0f, 1.0f, 0.0f }, Colors::Green);
	SimpleDraw::AddFace({ 0.0f, 0.0f, 0.0f }, { 2.0f, 1.0f, 0.0f }, { 2.0f, 0.0f, 0.0f }, Colors::Cyan);*/
	//SimpleDraw::AddAABB({ -1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f }, Colors::Pink);
	//SimpleDraw::AddSphere(160, 60, 2.0f, Colors::Yellow);
	SimpleDraw::AddGroundPlane(10, Colors::White);
	//SimpleDraw::AddGroundCircle(100, 2, Colors::White);
	SimpleDraw::AddTransform(Matrix4::Identity);
	SimpleDraw::Render(mCamera);
}