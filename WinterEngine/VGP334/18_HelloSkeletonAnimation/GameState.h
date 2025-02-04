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
	WinterEngine::Graphics::DirectionalLight mDirectionalLight;
	WinterEngine::Graphics::StandardEffect mStandardEffect;
	
	WinterEngine::Graphics::RenderGroup mCharacter;
	WinterEngine::Graphics::Animator mCharacterAnimator;

	WinterEngine::Graphics::RenderObject mGround;

	bool mShowSkeleton = false;
	int mAnimationIndex = -1;
};