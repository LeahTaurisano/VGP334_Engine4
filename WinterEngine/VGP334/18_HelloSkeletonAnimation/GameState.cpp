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

	mCharacter.Initialize(L"../../Assets/Models/Character01/Nightshade_J_Friedrich.model", &mCharacterAnimator);
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Character01/RumbaDancing.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Character01/Capoeira.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Character01/HipHopDancing.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Character01/Reaction.model");
	mCharacterAnimator.Initialize(mCharacter.modelId);

	Mesh groundMesh = MeshBuilder::CreateGroundPlane(10, 10, 1.0f);
	mGround.meshBuffer.Initialize(groundMesh);
	mGround.diffuseMapId = TextureCache::Get()->LoadTexture("misc/concrete.jpg");
}
void GameState::Terminate()
{
	mGround.Terminate();
	mCharacter.Terminate();
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

	mCharacterAnimator.Update(deltaTime);
}
void GameState::Render()
{
	mStandardEffect.Begin();
	if (mShowSkeleton)
	{
		AnimationUtil::BoneTransforms boneTransforms;
		AnimationUtil::ComputeBoneTransforms(mCharacter.modelId, boneTransforms, &mCharacterAnimator);
		AnimationUtil::DrawSkeleton(mCharacter.modelId, boneTransforms);
	}
	else
	{
		mStandardEffect.Render(mCharacter);
	}
		mStandardEffect.Render(mGround);
	mStandardEffect.End();
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
	ImGui::Checkbox("ShowSkeleton", &mShowSkeleton);

	int maxAnimations = mCharacterAnimator.GetAnimationCount();
	if (ImGui::DragInt("AnimIndex", &mAnimationIndex, 1, -1, maxAnimations - 1))
	{
		mCharacterAnimator.PlayAnimation(mAnimationIndex, true);
	}
	mStandardEffect.DebugUI();
	ImGui::End();

	SimpleDraw::Render(mCamera);
}