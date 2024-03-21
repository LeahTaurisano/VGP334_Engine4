#include "GameState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 500.0f, -200.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mSkysphereMesh = MeshBuilder::CreateSkySpherePX(2000, 2000, 6500.0f);
	mSkysphereMeshBuffer.Initialize(mSkysphereMesh);
	mSkysphereTexture.Initialize(L"../../Assets/Images/skysphere/space.jpg");

	mSun =     Planet(100, 100, 100.0f,    0.0f,    1.0f / 2.3f,          1.0f, L"../../Assets/Images/planets/sun.jpg");
	mMercury = Planet(100, 100, 0.333f,  157.0f,    1.0f / 4.0f,          4.0f, L"../../Assets/Images/planets/mercury.jpg");
	mVenus =   Planet(100, 100,  0.87f,  208.0f, -(1.0f /16.2f),          1.6f, L"../../Assets/Images/planets/venus.jpg");
	mEarth =   Planet(100, 100,   1.0f,  249.0f,          15.0f,          1.0f, L"../../Assets/Images/planets/earth/earth.jpg");
	mMars =    Planet(100, 100,   0.5f,  328.0f,          15.3f,   1.0f / 1.8f, L"../../Assets/Images/planets/mars.jpg");
	mJupiter = Planet(100, 100,  11.0f,  878.0f,          33.0f,  1.0f / 11.8f, L"../../Assets/Images/planets/jupiter.jpg");
	mSaturn =  Planet(100, 100,   9.0f, 1430.0f,          31.5f,  1.0f / 29.4f, L"../../Assets/Images/planets/saturn.jpg");
	mUranus =  Planet(100, 100,   4.0f, 2870.0f,          21.0f,  1.0f / 84.0f, L"../../Assets/Images/planets/uranus.jpg");
	mNeptune = Planet(100, 100,   3.7f, 4500.0f,          22.5f, 1.0f / 164.0f, L"../../Assets/Images/planets/neptune.jpg");
	mPluto =   Planet(100, 100,   0.2f, 5910.0f,           2.5f, 1.0f / 147.0f, L"../../Assets/Images/planets/pluto.jpg");

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
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 500.0f : 25.0f;
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

	mSun.Update(deltaTime * mTimeMod);
	mMercury.Update(deltaTime * mTimeMod);
	mVenus.Update(deltaTime * mTimeMod);
	mEarth.Update(deltaTime * mTimeMod);
	mMars.Update(deltaTime * mTimeMod);
	mJupiter.Update(deltaTime * mTimeMod);
	mSaturn.Update(deltaTime * mTimeMod);
	mUranus.Update(deltaTime * mTimeMod);
	mNeptune.Update(deltaTime * mTimeMod);
	mPluto.Update(deltaTime * mTimeMod);
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
	mSun.Render(mConstantBuffer, matView, matProj);
	mMercury.Render(mConstantBuffer, matView, matProj);
	mVenus.Render(mConstantBuffer, matView, matProj);
	mEarth.Render(mConstantBuffer, matView, matProj);
	mMars.Render(mConstantBuffer, matView, matProj);
	mJupiter.Render(mConstantBuffer, matView, matProj);
	mSaturn.Render(mConstantBuffer, matView, matProj);
	mUranus.Render(mConstantBuffer, matView, matProj);
	mNeptune.Render(mConstantBuffer, matView, matProj);
	mPluto.Render(mConstantBuffer, matView, matProj);

	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	ImGui::Begin("DebugUI", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	DebugUI::SetTheme(DebugUI::Theme::Dark);
	ImGui::LabelText("Debug Manager", "Solar System");
	ImGui::DragFloat("Time Scale", &mTimeMod, 0.1f, -100.0f, 100.0f);
	
	if (ImGui::Button("Mercury Orbit"))
	{
		mMercury.SetDrawOrbit(!mMercury.GetDrawOrbit());
	}
	if (mMercury.GetDrawOrbit())
	{
		SimpleDraw::AddGroundCircle(1000, mMercury.GetOrbit(), Colors::Red);
	}

	if (ImGui::Button("Venus Orbit"))
	{
		mVenus.SetDrawOrbit(!mVenus.GetDrawOrbit());
	}
	if (mVenus.GetDrawOrbit())
	{
		SimpleDraw::AddGroundCircle(1000, mVenus.GetOrbit(), Colors::OrangeRed);
	}

	if (ImGui::Button("Earth Orbit"))
	{
		mEarth.SetDrawOrbit(!mEarth.GetDrawOrbit());
	}
	if (mEarth.GetDrawOrbit())
	{
		SimpleDraw::AddGroundCircle(1000, mEarth.GetOrbit(), Colors::Orange);
	}

	if (ImGui::Button("Mars Orbit"))
	{
		mMars.SetDrawOrbit(!mMars.GetDrawOrbit());
	}
	if (mMars.GetDrawOrbit())
	{
		SimpleDraw::AddGroundCircle(1000, mMars.GetOrbit(), Colors::Yellow);
	}

	if (ImGui::Button("Jupiter Orbit"))
	{
		mJupiter.SetDrawOrbit(!mJupiter.GetDrawOrbit());
	}
	if (mJupiter.GetDrawOrbit())
	{
		SimpleDraw::AddGroundCircle(1000, mJupiter.GetOrbit(), Colors::Green);
	}

	if (ImGui::Button("Saturn Orbit"))
	{
		mSaturn.SetDrawOrbit(!mSaturn.GetDrawOrbit());
	}
	if (mSaturn.GetDrawOrbit())
	{
		SimpleDraw::AddGroundCircle(1000, mSaturn.GetOrbit(), Colors::Teal);
	}

	if (ImGui::Button("Uranus Orbit"))
	{
		mUranus.SetDrawOrbit(!mUranus.GetDrawOrbit());
	}
	if (mUranus.GetDrawOrbit())
	{
		SimpleDraw::AddGroundCircle(1000, mUranus.GetOrbit(), Colors::Blue);
	}

	if (ImGui::Button("Neptune Orbit"))
	{
		mNeptune.SetDrawOrbit(!mNeptune.GetDrawOrbit());
	}
	if (mNeptune.GetDrawOrbit())
	{
		SimpleDraw::AddGroundCircle(1000, mNeptune.GetOrbit(), Colors::Indigo);
	}

	if (ImGui::Button("Pluto Orbit"))
	{
		mPluto.SetDrawOrbit(!mPluto.GetDrawOrbit());
	}
	if (mPluto.GetDrawOrbit())
	{
		SimpleDraw::AddGroundCircle(1000, mPluto.GetOrbit(), Colors::Violet);
	}

	ImGui::End();
}