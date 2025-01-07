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
	
	WinterEngine::Graphics::RenderObject mBall;
	WinterEngine::Graphics::RenderObject mGround;

	WinterEngine::Graphics::DirectionalLight mDirectionalLight;
	WinterEngine::Graphics::StandardEffect mStandardEffect;

	//animation
	WinterEngine::Graphics::Animation mAnimation;
	float mAnimationTime = 0.0f;
};