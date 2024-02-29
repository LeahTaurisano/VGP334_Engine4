#pragma once

#include <WinterEngine/Inc/WinterEngine.h>

using namespace WinterEngine;

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
	float mSphereAlpha = 1.0f;
	Math::Vector3 mPosition = Math::Vector3::Zero;
};