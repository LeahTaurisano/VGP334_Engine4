#pragma once

#include <WinterEngine/Inc/WinterEngine.h>

using namespace WinterEngine;
using namespace WinterEngine::Graphics;

class Planet
{
public:
	Planet();
	Planet(uint32_t slices, uint32_t rings, float radius, float distance, std::filesystem::path filePath);
	void Terminate();
	void Render(ConstantBuffer constantBuffer);

private:
	Math::Vector3 mPosition;
	Math::Vector3 mRotation;

	MeshPX mMesh;
	MeshBuffer mMeshBuffer;
	Texture mTexture;
};