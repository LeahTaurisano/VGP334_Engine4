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
	WinterEngine::Graphics::Camera mRenderTargetCamera;
	
	WinterEngine::Graphics::RenderGroup mCharacter;
	WinterEngine::Graphics::RenderGroup mCharacter2;

	WinterEngine::Graphics::RenderGroup toRenderTarget;

	WinterEngine::Graphics::StandardEffect mStandardEffect;
	WinterEngine::Graphics::StandardEffect mRenderTargetStandardEffect;
	WinterEngine::Graphics::DirectionalLight mDirectionalLight;
	WinterEngine::Graphics::RenderTarget mRenderTarget;
};