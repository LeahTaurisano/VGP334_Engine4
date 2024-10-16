#pragma once

#include <WinterEngine/Inc/WinterEngine.h>

class GameState : public WinterEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

protected:
	WinterEngine::Graphics::Camera mCamera;
	std::vector<WinterEngine::Graphics::RenderObject> mPlanets;

	WinterEngine::Graphics::StandardEffect mStandardEffect;
	WinterEngine::Graphics::DirectionalLight mDirectionalLight;
};