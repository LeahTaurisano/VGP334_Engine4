#include "GameState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 2.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 1.0f, 0.0f });

	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	mPortalEffectOne.Initialize();
	mPortalEffectOne.SetStandardEffect(mStandardEffect);
	mPortalEffectOne.SetGameCamera(mCamera);
	mPortalEffectTwo.Initialize();
	mPortalEffectTwo.SetStandardEffect(mStandardEffect);
	mPortalEffectTwo.SetGameCamera(mCamera);

	mPortalEffectOne.LinkPortal(mPortalEffectTwo);
	mPortalEffectTwo.LinkPortal(mPortalEffectOne);

	MeshPX portalOneMesh = MeshBuilder::CreateVerticalPlanePX(1, 1, 2.0f);
	mPortalOne.meshBuffer.Initialize(portalOneMesh);
	mPortalOne.transform.position = { 2.0f, 1.5f, 1.0f };
	mPortalEffectOne.SetPortalObject(mPortalOne);

	MeshPX portalTwoMesh = MeshBuilder::CreateVerticalPlanePX(1, 1, 2.0f);
	mPortalTwo.meshBuffer.Initialize(portalTwoMesh);
	mPortalTwo.transform.position = { -2.0f, 1.5f, 1.0f };
	mPortalEffectTwo.SetPortalObject(mPortalTwo);
	
	mCharacter.Initialize(L"../../Assets/Models/Character01/Nightshade_J_Friedrich.model");
	mCharacter.transform.position = { 2.0f, 0.0f, -2.0f };

	Mesh groundMesh = MeshBuilder::CreateGroundPlane(10, 10, 1.0f);
	mGround.meshBuffer.Initialize(groundMesh);
	mGround.diffuseMapId = TextureCache::Get()->LoadTexture("misc/concrete.jpg");

	GraphicsSystem* gs = GraphicsSystem::Get();
	const uint32_t screenWidth = gs->GetBackBufferWidth();
	const uint32_t screenHeight = gs->GetBackBufferHeight();
	mRenderTarget.Initialize(screenWidth, screenHeight, Texture::Format::RGBA_U8);
}
void GameState::Terminate()
{
	mRenderTarget.Terminate();
	mGround.Terminate();
	mCharacter.Terminate();
	mPortalTwo.Terminate();
	mPortalOne.Terminate();
	mPortalEffectTwo.Terminate();
	mPortalEffectOne.Terminate();
	mStandardEffect.Terminate();
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

	if (input->IsKeyDown(KeyCode::LEFT))
	{
		mCharacter.transform.position.x -= (moveSpeed * deltaTime);
	}
}
void GameState::Render()
{
	// portal 1
	// set standard effect camera to linked camera
	// render
	//======================================
	// repeat for portal 2
	// set standard effect camera to linked camera
	//// render
	//mPortal1Effect.BeginPortalImageRender(); // getting the image
	//	//		mRendertarget.BeginRender()
	//	//		mStandardEffect->SetCamera(mLinkedCamera)
	//	//		mStandardEffect->Begin()
	//	///mStandardEffect.Begin();
	//	mPortal1Effect.Render(mCharacter);
	//	mPortal1Effect.Render(mGround);
	//	//mStandardEffect.End();
	//mPortal1Effect.EndPortalImageRender();
	//	// mStandardEffect->End()
	//	//	mRenderTarget.EndRender()

	mPortalEffectOne.BeginPortalImageRender();
		mPortalEffectOne.PortalImageRender(mCharacter);
		mPortalEffectOne.PortalImageRender(mGround);
	mPortalEffectOne.EndPortalImageRender();

	mPortalEffectTwo.BeginPortalImageRender();
		mPortalEffectTwo.PortalImageRender(mCharacter);
		mPortalEffectTwo.PortalImageRender(mGround);
	mPortalEffectTwo.EndPortalImageRender();

	mPortalEffectOne.Begin();
	mPortalEffectOne.Render(mPortalOne);
	mPortalEffectOne.End();

	mPortalEffectTwo.Begin();
	mPortalEffectTwo.Render(mPortalTwo);
	mPortalEffectTwo.End();

	mStandardEffect.Begin();
		mStandardEffect.Render(mCharacter);
		mStandardEffect.Render(mGround);
	mStandardEffect.End();

	//mPortal2Effect.BeginPortalImageRender(); // getting the image
	////		mRendertarget.BeginRender()
	////		mStandardEffect->SetCamera(mLinkedCamera)
	////		mStandardEffect->Begin()
	/////mStandardEffect.Begin();
	//mPortal2Effect.Render(mCharacter);
	//mPortal2Effect.Render(mGround);
	////mStandardEffect.End();
	//mPortal2Effect.EndPortalImageRender();
	//// mStandardEffect->End()
	////	mRenderTarget.EndRender()

	//mPortal1Effect.Begin();
	//	// in the render
	//	//	mRenderTarget.BindPS(0)
	//	mPortal1Effect.Render(mPortal1Object);
	//mPortal1Effect.End();

	//mPortal2Effect.Begin();
	//	mPortal2Effect.Render(mPortal2Object);
	//mPortal2Effect.End();

	//mStandardEffect.SetCamera(mPortal1Effect.GetLinkedCamera());
	//mPortal1Effect.BeginPortalRender(); // getting the image
	//	mStandardEffect.Begin();
	//	mStandardEffect.Render(mCharacter);
	//	mStandardEffect.Render(mGround);
	//	mStandardEffect.End();
	//mPortal1Effect.EndPortalRender();

	// render portal 1 with the portal object
	// render portal 2 with the other portal object
	//mPostProcessingEffect.Begin();
	//mPostProcessingEffect.Render(mScreenQuad);
	//mPostProcessingEffect.End();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.1f))
		{
			mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
		}

		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}
	ImGui::Separator();
	ImGui::Text("RenderTarget");
	ImGui::Image(
		mRenderTarget.GetRawData(),
		{ 128, 128 },
		{ 0, 0 },
		{ 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 });
	mPortalEffectOne.DebugUI();
	mPortalEffectTwo.DebugUI();
	mStandardEffect.DebugUI();
	ImGui::End();
}