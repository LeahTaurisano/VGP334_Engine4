#pragma once

#include <WinterEngine/Inc/WinterEngine.h>
#include "Planet.h"

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
	WinterEngine::Graphics::ConstantBuffer mConstantBuffer;
	WinterEngine::Graphics::VertexShader mVertexShader;
	WinterEngine::Graphics::PixelShader mPixelShader;
	WinterEngine::Graphics::Sampler mSampler;

	WinterEngine::Graphics::MeshPX mSkysphereMesh;
	WinterEngine::Graphics::MeshBuffer mSkysphereMeshBuffer;
	WinterEngine::Graphics::Texture mSkysphereTexture;

	Planet mSun;
	Planet mMercury;
	Planet mVenus;
	Planet mEarth;
	Planet mMars;
	Planet mJupiter;
	Planet mSaturn;
	Planet mUranus;
	Planet mNeptune;
	Planet mPluto;

	float mTimeMod = 1.0f;
};