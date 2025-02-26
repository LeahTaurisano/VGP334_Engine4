#include "Precompile.h"
#include "App.h"
#include "AppState.h"
#include "EventManager.h"

using namespace WinterEngine;
using namespace WinterEngine::Core;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Input;
using namespace WinterEngine::Physics;
using namespace WinterEngine::Audio;

void App::ChangeState(const std::string& stateName)
{
	auto iter = mAppStates.find(stateName);
	if (iter != mAppStates.end())
	{
		mNextState = iter->second.get();
	}
}

void App::Run(const AppConfig& config)
{
	LOG("App Started: %.3f", TimeUtil::GetTime());
	
	Window myWindow;
	myWindow.Initialize(
		GetModuleHandle(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight
	);
	ASSERT(myWindow.IsActive(), "Failed to create a window");
	auto handle = myWindow.GetWindowHandle();
	GraphicsSystem::StaticInitialize(handle, false);
	InputSystem::StaticInitialize(handle);
	SimpleDraw::StaticInitialize(config.maxVertexCount);
	DebugUI::StaticInitialize(handle, false, true);
	TextureCache::StaticInitialize("../../Assets/Images/");
	ModelCache::StaticInitialize();
	EventManager::StaticInitialize();
	AudioSystem::StaticInitialize();
	SoundEffectManager::StaticInitialize("../../Assets/Sounds/");
	
	PhysicsWorld::Settings settings;
	PhysicsWorld::StaticInitialize(settings);

	ASSERT(mCurrentState != nullptr, "App: need an app state");
	mCurrentState->Initialize();

	mRunning = true;
	while (mRunning)
	{
		myWindow.ProcessMessage();
		InputSystem* input = InputSystem::Get();
		input->Update();

		if (!myWindow.IsActive() || input->IsKeyPressed(KeyCode::ESCAPE))
		{
			Quit();
			break;
		}

		AudioSystem::Get()->Update();

		if (mNextState != nullptr)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
		}

		float deltaTime = TimeUtil::GetDeltaTime();
		mCurrentState->Update(deltaTime);
		PhysicsWorld::Get()->Update(deltaTime);
		
		GraphicsSystem* gs = GraphicsSystem::Get();
		gs->BeginRender();
			mCurrentState->Render();
			DebugUI::BeginRender();
				mCurrentState->DebugUI();
			DebugUI::EndRender();
		gs->EndRender();
	}

	mCurrentState->Terminate();


	PhysicsWorld::StaticTerminate();
	SoundEffectManager::StaticTerminate();
	AudioSystem::StaticTerminate();
	EventManager::StaticTerminate();
	ModelCache::StaticTerminate();
	TextureCache::StaticTerminate();
	SimpleDraw::StaticTerminate();
	DebugUI::StaticTerminate();
	InputSystem::StaticTerminate();
	GraphicsSystem::StaticTerminate();
	myWindow.Terminate();
}

void App::Quit()
{
	mRunning = false;
}