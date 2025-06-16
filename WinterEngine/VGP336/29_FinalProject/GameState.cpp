#include "GameState.h"
#include "CustomDebugDrawService.h"
#include "CustomDebugDrawComponent.h"
#include "CustomPlayerControllerComponent.h"
#include "CustomSideScrollingComponent.h"
#include "CustomProjectileComponent.h"
#include "CustomProjectileSpawnerService.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Input;
using namespace WinterEngine::Audio;
using namespace WinterEngine::Physics;

Service* CustomServiceMake(const std::string& serviceName, GameWorld& gameWorld)
{
	if (serviceName == "CustomDebugDrawService")
	{
		return gameWorld.AddService<CustomDebugDrawService>();
	}
	if (serviceName == "CustomProjectileSpawnerService")
	{
		return gameWorld.AddService<CustomProjectileSpawnerService>();
	}
	return nullptr;
}

Component* CustomComponentMake(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "CustomDebugDrawComponent")
	{
		return gameObject.AddComponent<CustomDebugDrawComponent>();
	}
	if (componentName == "CustomPlayerControllerComponent")
	{
		return gameObject.AddComponent<CustomPlayerControllerComponent>();
	}
	if (componentName == "CustomSideScrollingComponent")
	{
		return gameObject.AddComponent<CustomSideScrollingComponent>();
	}
	if (componentName == "CustomProjectileComponent")
	{
		return gameObject.AddComponent<CustomProjectileComponent>();
	}
	return nullptr;
}

Component* CustomComponentGet(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "CustomDebugDrawComponent")
	{
		return gameObject.GetComponent<CustomDebugDrawComponent>();
	}
	if (componentName == "CustomPlayerControllerComponent")
	{
		return gameObject.GetComponent<CustomPlayerControllerComponent>();
	}
	if (componentName == "CustomProjectileComponent")
	{
		return gameObject.GetComponent<CustomProjectileComponent>();
	}
	return nullptr;
}

void GameState::Initialize()
{
	// adds delegate callback to create a custom service
	GameWorld::SetCustomService(CustomServiceMake);
	GameObjectFactory::SetCustomMake(CustomComponentMake);
	GameObjectFactory::SetCustomGet(CustomComponentGet);

	mGameWorld.LoadLevel(L"../../Assets/Templates/Levels/final_level.json");
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
	UIFont::Get()->DrawString(L"Hello World", Vector2::Zero, Colors::White);
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	mGameWorld.DebugUI();
	ImGui::End();
}