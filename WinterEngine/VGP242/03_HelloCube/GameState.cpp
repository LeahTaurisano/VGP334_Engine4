#include "GameState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mMesh.vertices.push_back({ {-0.5f, -0.5f, -0.5f}, Colors::Red });
	mMesh.vertices.push_back({ {-0.5f, 0.5f, -0.5f}, Colors::Pink });
	mMesh.vertices.push_back({ {0.5f, 0.5f, -0.5f}, Colors::Purple });
	mMesh.vertices.push_back({ {0.5f, -0.5f, -0.5f}, Colors::FloralWhite });

	mMesh.vertices.push_back({ {-0.5f, -0.5f, 0.5f}, Colors::Red });
	mMesh.vertices.push_back({ {-0.5f, 0.5f, 0.5f}, Colors::Pink });
	mMesh.vertices.push_back({ {0.5f, 0.5f, 0.5f}, Colors::Purple });
	mMesh.vertices.push_back({ {0.5f, -0.5f, 0.5f}, Colors::FloralWhite });

	mMesh.indices = {
    	//front
		0, 1, 2,
		0, 2, 3,
		//back
		7, 5, 4,
		7, 6, 5,
		//right
		3, 2, 6,
		3, 6, 7,
		//left
		4, 5, 1,
		4, 1, 0,
		//top
		1, 5, 6,
		1, 6, 2,
		//bottom
		0, 3, 7,
		0, 7, 4
	};

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/DoTransform.fx";
	mConstantBuffer.Initialize(sizeof(Math::Matrix4));
	mMeshBuffer.Initialize(mMesh);
	mVertexShader.Initialize<VertexPC>(shaderFilePath);
	mPixelShader.Initialize(shaderFilePath);

}
void GameState::Terminate()
{
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
	mPixelShader.Terminate();
	mConstantBuffer.Terminate();

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

	Math::Matrix4 matWorld = Math::Matrix4::Identity;
	Math::Matrix4 matView = mCamera.GetViewMatrix();
	Math::Matrix4 matProj = mCamera.GetProjectionMatrix();
	Math::Matrix4 matFinal = matWorld * matView * matProj;
	Math::Matrix4 wvp = Transpose(matFinal);

	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();
}