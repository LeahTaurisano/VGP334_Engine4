#include "Precompile.h"
#include "CameraComponent.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Math;

void CameraComponent::Initialize()
{
}

void CameraComponent::Terminate()
{
}

void CameraComponent::DebugUI()
{
	Vector3 pos = mCamera.GetPosition();
	if (ImGui::DragFloat3("Position##Camera", &pos.x, 0.1f))
	{
		mCamera.SetPosition(pos);
	}
}

Graphics::Camera& CameraComponent::GetCamera()
{
	return mCamera;
}

const Graphics::Camera& CameraComponent::GetCamera() const
{
	return mCamera;
}
