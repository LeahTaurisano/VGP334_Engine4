#include "GameState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Input;
using namespace WinterEngine::Physics;

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

	Mesh ball = MeshBuilder::CreateSphere(60, 60, 0.5f);
	mBall.meshBuffer.Initialize(ball);
	mBall.diffuseMapId = TextureCache::Get()->LoadTexture("misc/basketball.jpg");

	mBallShape.InitializeSphere(0.5f);
	mBallRB.Initialize(mBall.transform, mBallShape, 10.0f);

	Mesh ground = MeshBuilder::CreateGroundPlane(10, 10, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureCache::Get()->LoadTexture("misc/concrete.jpg");

	mGroundShape.InitializeHull({ 5.0f, 0.5f, 5.0f }, { 0.0f, -0.5f, 0.0f });
	mGroundRB.Initialize(mGround.transform, mGroundShape);

	Mesh boxShape = MeshBuilder::CreateCube(1.0f);
	TextureId boxTexture = TextureCache::Get()->LoadTexture("sprites/yellow.jpg");

	float yOffset = 4.5f;
	float xOffset = 0.0f;
	int rowCount = 1;
	int boxIndex = 0;
	mBoxes.resize(10);
	while (boxIndex < 10)
	{
		xOffset = -((static_cast<float>(rowCount) - 1.0f) * 0.5f);
		for (int r = 0; r < rowCount; ++r)
		{
			BoxData& newBox = mBoxes[boxIndex];
			newBox.box.meshBuffer.Initialize(boxShape);
			newBox.box.diffuseMapId = boxTexture;
			newBox.box.transform.position = { xOffset, yOffset, -4.0f };
			newBox.boxShape.InitializeBox({ 0.5f, 0.5f, 0.5f });
			xOffset += 1.0f;
			++boxIndex;
		}
		yOffset -= 1.0f;
		rowCount += 1;
	}

	for (BoxData& box : mBoxes)
	{
		box.boxRB.Initialize(box.box.transform, box.boxShape, 5.0f);
	}

	int rows = 20;
	int cols = 20;
	mClothMesh = MeshBuilder::CreateGroundPlane(rows, cols, 0.5f);
	for (Vertex& v : mClothMesh.vertices)
	{
		v.position.y = 10.0f;
	}
	uint32_t lastVertex = mClothMesh.vertices.size() - 1;
	uint32_t lastVertexOS = lastVertex - cols;
	mClothSoftBody.Initialize(mClothMesh, 1.0f, { lastVertex, lastVertexOS });

	mCloth.meshBuffer.Initialize(nullptr, sizeof(Vertex), mClothMesh.vertices.size(), mClothMesh.indices.data(), mClothMesh.indices.size());
	mCloth.diffuseMapId = TextureCache::Get()->LoadTexture("sprites/splashscreen.bmp");
}
void GameState::Terminate()
{
	for (BoxData& box : mBoxes)
	{
		box.boxRB.Terminate();
		box.boxShape.Terminate();
	}

	mCloth.Terminate();
	mClothSoftBody.Terminate();
	mGroundRB.Terminate();
	mGroundShape.Terminate();
	mBallRB.Terminate();
	mBallShape.Terminate();
	mGround.Terminate();
	mBall.Terminate();
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

	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	{
		mBallRB.SetVelocity({ 0.0f, 10.0f, 0.0f });
	}
	if (InputSystem::Get()->IsMousePressed(MouseButton::LBUTTON))
	{
		Math::Vector3 spawnPos = mCamera.GetPosition() + (mCamera.GetDirection() * 0.5f);
		mBallRB.SetPosition(spawnPos);
		mBallRB.SetVelocity(mCamera.GetDirection() * 20.0f);
	}
}
void GameState::Render()
{
	mCloth.meshBuffer.Update(mClothMesh.vertices.data(), mClothMesh.vertices.size());
	mStandardEffect.Begin();
		mStandardEffect.Render(mGround);
		mStandardEffect.Render(mBall);
		for (BoxData& box : mBoxes)
		{
			mStandardEffect.Render(box.box);
		}
		mStandardEffect.Render(mCloth);
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
	mStandardEffect.DebugUI();
	PhysicsWorld::Get()->DebugUI();
	ImGui::End();

	SimpleDraw::Render(mCamera);
}	