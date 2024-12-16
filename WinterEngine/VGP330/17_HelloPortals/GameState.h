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
	WinterEngine::Graphics::PortalEffect mPortalEffectOne;
	WinterEngine::Graphics::PortalEffect mPortalEffectTwo;

	WinterEngine::Graphics::RenderGroup mCharacter;
	WinterEngine::Graphics::RenderObject mGround;

	WinterEngine::Graphics::RenderTarget mRenderTarget;

	WinterEngine::Graphics::RenderObject mPortalOne;
	WinterEngine::Graphics::RenderObject mPortalTwo;

	WinterEngine::Graphics::RenderObject sphereObject;
	WinterEngine::Graphics::RenderObject sphereObject2;
};