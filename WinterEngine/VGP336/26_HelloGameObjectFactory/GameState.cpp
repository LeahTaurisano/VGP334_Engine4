#include "GameState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Input;
using namespace WinterEngine::Audio;
using namespace WinterEngine::Physics;

void GameState::Initialize()
{
	mGameWorld.AddService<CameraService>();
	mGameWorld.AddService<RenderService>();
	mGameWorld.Initialize();

	GameObject* transformGO = mGameWorld.CreateGameObject("Transform", L"../../Assets/Templates/mesh_obj.json");
	transformGO->Initialize();

	GameObject* cameraGO = mGameWorld.CreateGameObject("Camera", L"../../Assets/Templates/fps_camera.json");
	cameraGO->Initialize();
}
void GameState::Terminate()
{
	mGameWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
	mGameWorld.Update(deltaTime);
}

void GameState::Render()
{
	mGameWorld.Render();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	mGameWorld.DebugUI();
	ImGui::End();
}