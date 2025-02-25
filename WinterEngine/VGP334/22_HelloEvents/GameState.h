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
	void OnMoveEvent();
	void OneSpacePressedEvent(const WinterEngine::Event& e);

	WinterEngine::Graphics::Camera mCamera;
	
	WinterEngine::Graphics::RenderObject mBall;
	WinterEngine::Graphics::RenderObject mGround;

	WinterEngine::Graphics::DirectionalLight mDirectionalLight;
	WinterEngine::Graphics::StandardEffect mStandardEffect;

	WinterEngine::Math::Vector3 mOffset = WinterEngine::Math::Vector3::Zero;
	WinterEngine::ListenerId mSpacePressedEventId = 0;

	WinterEngine::Audio::SoundId mGunEventId = 0;
	WinterEngine::Audio::SoundId mExplosionEventId = 0;

	//animation
	WinterEngine::Graphics::Animation mAnimation;
	float mAnimationTime = 0.0f;
};