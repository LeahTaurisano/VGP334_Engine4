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
	
}

bool buttonOn = false;
void GameState::DebugUI()
{
	ImGui::Begin("DebugUI", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	DebugUI::SetTheme(DebugUI::Theme::Dark);
	ImGui::LabelText("Title", "Hello ImGui");
	if (ImGui::Button("Button"))
	{
		buttonOn = !buttonOn;
	}
	if (buttonOn)
	{
		ImGui::LabelText("ButtonOn", "Button Pressed");
	}
	if (ImGui::CollapsingHeader("Info", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("SphereAlpha", &mSphereAlpha, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat3("TransformPos", &mPosition.x, 0.01f, -2.0f, 2.0f);
	}

	ImGui::End();

	SimpleDraw::AddTransform(Math::Matrix4::Translation(mPosition));
	SimpleDraw::AddGroundPlane(10, Colors::White);
	SimpleDraw::AddSphere(60, 60, 1.0f, { 1.0f, 1.0f, 0.0f, mSphereAlpha });
	SimpleDraw::Render(mCamera);
}
