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
	WinterEngine::Graphics::GaussianBlurEffect mGaussianBlurEffect;
	WinterEngine::Graphics::PostProcessingEffect mPostProcessingEffect;

	WinterEngine::Graphics::RenderGroup mCharacter;
	WinterEngine::Graphics::RenderObject mGround;
	WinterEngine::Graphics::RenderObject mScreenQuad;

	WinterEngine::Graphics::RenderTarget mRenderTarget;
	WinterEngine::Graphics::RenderTarget mBloomRenderTarget;
};