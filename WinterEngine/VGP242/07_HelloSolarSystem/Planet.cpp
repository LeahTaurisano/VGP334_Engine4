#include "Planet.h"

Planet::Planet()
{
}

Planet::Planet(uint32_t slices, uint32_t rings, float radius, float distance, std::filesystem::path filePath)
{
	mMesh = MeshBuilder::CreateSpherePX(slices, rings, radius);
	mMeshBuffer.Initialize(mMesh);
	mTexture.Initialize(filePath);

	mPosition = { 0.0f, 0.0f, distance };
}

void Planet::Terminate()
{
	mMeshBuffer.Terminate();
	mTexture.Terminate();
}

void Planet::Render(ConstantBuffer constantBuffer)
{
	mTexture.BindPS(0);
	constantBuffer.BindVS(0);

	mMeshBuffer.Render();
}
