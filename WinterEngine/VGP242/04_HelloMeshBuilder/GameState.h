#pragma once

#include <WinterEngine/Inc/WinterEngine.h>

class GameState : public WinterEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	WinterEngine::Graphics::Camera mCamera;
	WinterEngine::Graphics::MeshPX mMesh;
	WinterEngine::Graphics::ConstantBuffer mConstantBuffer;
	WinterEngine::Graphics::MeshBuffer mMeshBuffer;
	WinterEngine::Graphics::VertexShader mVertexShader;
	WinterEngine::Graphics::PixelShader mPixelShader;

	WinterEngine::Graphics::Texture mTexture;
	WinterEngine::Graphics::Sampler mSampler;
};