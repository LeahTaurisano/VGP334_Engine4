#pragma once

#include <WinterEngine/Inc/WinterEngine.h>

class GameState : public WinterEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

protected:
	WinterEngine::Graphics::Camera mCamera;
	
	WinterEngine::Graphics::RenderObject mBall;
	WinterEngine::Physics::CollisionShape mBallShape;
	WinterEngine::Physics::RigidBody mBallRB;

	WinterEngine::Graphics::RenderObject mGround;
	WinterEngine::Physics::CollisionShape mGroundShape;
	WinterEngine::Physics::RigidBody mGroundRB;

	WinterEngine::Graphics::DirectionalLight mDirectionalLight;
	WinterEngine::Graphics::StandardEffect mStandardEffect;

	struct BoxData
	{
		WinterEngine::Graphics::RenderObject box;
		WinterEngine::Physics::CollisionShape boxShape;
		WinterEngine::Physics::RigidBody boxRB;
	};
	using Boxes = std::vector<BoxData>;
	Boxes mBoxes;

	WinterEngine::Graphics::RenderObject mCloth;
	WinterEngine::Graphics::Mesh mClothMesh;
	WinterEngine::Physics::SoftBody mClothSoftBody;
};