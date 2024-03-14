#include "Planet.h"

Planet::Planet()
{
}

Planet::Planet(uint32_t slices, uint32_t rings, float radius, float distance, float rotation, float orbit, std::filesystem::path filePath)
{
	mMesh = MeshBuilder::CreateSpherePX(slices, rings, radius);
	mMeshBuffer.Initialize(mMesh);
	mTexture.Initialize(filePath);

	mPosition = { 0.0f, 0.0f, distance };
	mRotation = 0;
	mRotationSpeed = rotation;
	mOrbit = 0;
	mOrbitSpeed = orbit;
}

void Planet::Terminate()
{
	mMeshBuffer.Terminate();
	mTexture.Terminate();
}

void Planet::Update(float deltaTime)
{
	mRotation += mRotationSpeed * deltaTime;
	while (mRotation > 360)
	{
		mRotation -= 360;
	}
	mOrbit += mOrbitSpeed * deltaTime;
	while (mOrbit > 360)
	{
		mOrbit -= 360;
	}
}

void Planet::Render(ConstantBuffer constantBuffer, Math::Matrix4 matView, Math::Matrix4 matProj)
{
	mTexture.BindPS(0);
	constantBuffer.BindVS(0);
	Math::Matrix4 matRotation = Math::Matrix4::RotationY(mRotation * Math::Constants::DegToRad);
	Math::Matrix4 matTranslation = Math::Matrix4::Translation(mPosition);
	Math::Matrix4 matOrbit = Math::Matrix4::RotationY(mOrbit * Math::Constants::DegToRad);
	Math::Matrix4 matWorld = matRotation * matTranslation * matOrbit;
	Math::Matrix4 matFinal = matWorld * matView * matProj;
	Math::Matrix4 wvp = Transpose(matFinal);
	constantBuffer.Update(&wvp);

	mMeshBuffer.Render();
}

void Planet::SetDrawOrbit(bool state)
{
	mDrawOrbit = state;
}

bool Planet::GetDrawOrbit()
{
	return mDrawOrbit;
}

float Planet::GetOrbit()
{
	return mPosition.z;
}
