#include "Precompile.h"
#include "StandardEffect.h"
#include "VertexTypes.h"
#include "Camera.h"
#include "RenderObject.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;

void StandardEffect::Initialize(const std::filesystem::path& path)
{	 
	mVertexShader.Initialize<Vertex>(path);
	mPixelShader.Initialize(path);
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	mTransformBuffer.Initialize();
}	 
	 
void StandardEffect::Terminate()
{	 
	mTransformBuffer.Terminate();
	mSampler.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
}	 
	 
void StandardEffect::Begin()
{	 
	mVertexShader.Bind();
	mPixelShader.Bind();
	mSampler.BindPS(0);

	mTransformBuffer.BindVS(0);
}	 
	 
void StandardEffect::End()
{	 
	// shadows release textures
	// blends clear blend states
}	 
	 
void StandardEffect::Render(const RenderObject& renderObject)
{	 
	ASSERT(mCamera != nullptr, "StandardEffect: must have a camera");
	const Math::Matrix4 matWorld = renderObject.transform.GetMatrix4();
	const Math::Matrix4 matView = mCamera->GetViewMatrix();
	const Math::Matrix4 matProj = mCamera->GetProjectionMatrix();

	const Math::Matrix4 matFinal = matWorld * matView * matProj;
	TransformData transformData;
	transformData.wvp = Transpose(matFinal);
	mTransformBuffer.Update(transformData);

	TextureCache* tc = TextureCache::Get();
	tc->BindPS(renderObject.diffuseTextureId, 0);
	renderObject.meshBuffer.Render();
}	 
	 
void StandardEffect::SetCamera(const Camera& camera)
{	 
	mCamera = &camera;
}	 
	 
void StandardEffect::DebugUI()
{
}
