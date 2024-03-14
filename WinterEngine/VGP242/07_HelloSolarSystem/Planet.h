#pragma once

#include <WinterEngine/Inc/WinterEngine.h>

using namespace WinterEngine;
using namespace WinterEngine::Graphics;

class Planet
{
public:
	Planet();
	Planet(uint32_t slices, uint32_t rings, float radius, float distance, float rotation, float orbit, std::filesystem::path filePath);
	void Terminate();
	void Update(float deltaTime);
	void Render(ConstantBuffer constantBuffer, Math::Matrix4 matView, Math::Matrix4 matProj);

	void SetDrawOrbit(bool state);
	bool GetDrawOrbit();

	float GetOrbit();

private:
	Math::Vector3 mPosition;
	float mRotation;
	float mRotationSpeed;
	float mOrbit;
	float mOrbitSpeed;

	bool mDrawOrbit;

	MeshPX mMesh;
	MeshBuffer mMeshBuffer;
	Texture mTexture;
};