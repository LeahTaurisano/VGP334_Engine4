#include "GameState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mSkysphereMesh = MeshBuilder::CreateSkySpherePX(1000, 1000, 1000.0f);
	mSkysphereMeshBuffer.Initialize(mSkysphereMesh);
	mSkysphereTexture.Initialize(L"../../Assets/Images/skysphere/space.jpg");

	mSun = Planet(100, 100, 1.0f, 0.0f, L"../../Assets/Images/planets/sun.jpg");
	mMercury = Planet(100, 100, 1.0f, 1.0f, L"../../Assets/Images/planets/mercury.jpg");
	mVenus = Planet(100, 100, 1.0f, 2.0f, L"../../Assets/Images/planets/venus.jpg");
	mEarth = Planet(100, 100, 1.0f, 3.0f, L"../../Assets/Images/planets/earth/earth.jpg");
	mMars = Planet(100, 100, 1.0f, 4.0f, L"../../Assets/Images/planets/mars.jpg");
	mJupiter = Planet(100, 100, 1.0f, 5.0f, L"../../Assets/Images/planets/jupiter.jpg");
	mSaturn = Planet(100, 100, 1.0f, 6.0f, L"../../Assets/Images/planets/saturn.jpg");
	mUranus = Planet(100, 100, 1.0f, 7.0f, L"../../Assets/Images/planets/uranus.jpg");
	mNeptune = Planet(100, 100, 1.0f, 8.0f, L"../../Assets/Images/planets/neptune.jpg");
	mPluto = Planet(100, 100, 1.0f, 9.0f, L"../../Assets/Images/planets/pluto.jpg");

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/DoTexturing.fx";
	mConstantBuffer.Initialize(sizeof(Math::Matrix4));
	mVertexShader.Initialize<VertexPX>(shaderFilePath);
	mPixelShader.Initialize(shaderFilePath);
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

}
void GameState::Terminate()
{
	mVertexShader.Terminate();
	mSkysphereMeshBuffer.Terminate();
	mSun.Terminate();
	mMercury.Terminate();
	mVenus.Terminate();
	mEarth.Terminate();
	mMars.Terminate();
	mJupiter.Terminate();
	mSaturn.Terminate();
	mUranus.Terminate();
	mNeptune.Terminate();
	mPluto.Terminate();
	mPixelShader.Terminate();
	mConstantBuffer.Terminate();
	mSkysphereTexture.Terminate();
	mSampler.Terminate();
}
void GameState::Update(float deltaTime)
{
	auto input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;
	
	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}
void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mSampler.BindPS(0);
	mSkysphereTexture.BindPS(0);

	Math::Matrix4 matWorld = Math::Matrix4::Identity;
	Math::Matrix4 matView = mCamera.GetViewMatrix();
	Math::Matrix4 matProj = mCamera.GetProjectionMatrix();
	Math::Matrix4 matFinal = matWorld * matView * matProj;
	Math::Matrix4 wvp = Transpose(matFinal);

	mConstantBuffer.Update(&wvp);

	mSkysphereMeshBuffer.Render();
	mSun.Render(mConstantBuffer);
	mMercury.Render(mConstantBuffer);
	mVenus.Render(mConstantBuffer);
	mEarth.Render(mConstantBuffer);
	mMars.Render(mConstantBuffer);
	mJupiter.Render(mConstantBuffer);
	mSaturn.Render(mConstantBuffer);
	mUranus.Render(mConstantBuffer);
	mNeptune.Render(mConstantBuffer);
	mPluto.Render(mConstantBuffer);
}