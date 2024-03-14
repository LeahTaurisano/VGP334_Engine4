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
	void Update(float deltaTime, float rotationSpeed, float orbitSpeed);
	void Render(ConstantBuffer constantBuffer, Math::Matrix4 matView, Math::Matrix4 matProj);

private:
	Math::Vector3 mPosition;
	float mRotation;
	float mOrbit;

	MeshPX mMesh;
	MeshBuffer mMeshBuffer;
	Texture mTexture;
};