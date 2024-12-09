#include "Precompile.h"
#include "PortalEffect.h"

#include "VertexTypes.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;

void PortalEffect::Initialize()
{
	std::filesystem::path shaderFile = L"../../Assets/Shaders/Portal.fx";
	mVertexShader.Initialize<Vertex>(shaderFile);
	mPixelShader.Initialize(shaderFile);
	mTransformBuffer.Initialize();
	mPortalCamera.SetMode(Camera::ProjectionMode::Orthographic);
	mPortalCamera.SetNearPlane(1.0f);
	mPortalCamera.SetFarPlane(1000.0f);

	constexpr uint32_t depthMapResolution = 4096;
	mPortalRenderTarget.Initialize(depthMapResolution, depthMapResolution, Texture::Format::RGBA_U32);
}

void PortalEffect::Terminate()
{
	mPortalRenderTarget.Terminate();
	mTransformBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void PortalEffect::Begin()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mTransformBuffer.BindVS(0);

	mPortalRenderTarget.BeginRender();
}

void PortalEffect::End()
{
	mPortalRenderTarget.EndRender();
}

void PortalEffect::Render(const RenderObject& renderObject)
{
}

void PortalEffect::DebugUI()
{
}

void PortalEffect::LinkPortal(PortalEffect& linkPortal)
{
	mLinkedPortalCamera = linkPortal.GetPortalCamera();
}

Camera PortalEffect::GetPortalCamera()
{
	return mPortalCamera;
}
