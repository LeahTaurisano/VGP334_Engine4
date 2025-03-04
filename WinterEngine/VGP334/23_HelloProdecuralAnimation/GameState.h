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

	void UpdateActiveSegments();

	WinterEngine::Graphics::Camera mCamera;
	
	WinterEngine::Graphics::RenderObject mOrb;
	float mOrbRadius = 0;

	WinterEngine::Graphics::RenderObject mGround;
	WinterEngine::Physics::RigidBody mGroundRB;
	WinterEngine::Physics::CollisionShape mGroundShape;
	WinterEngine::Graphics::DirectionalLight mDirectionalLight;
	WinterEngine::Graphics::StandardEffect mStandardEffect;

	uint32_t numSegments = 0;
	int activeSegments = 0;
	struct BodyPart
	{
		WinterEngine::Graphics::RenderObject segment;
		float range = 0.0f;
		bool isActive = true;
	};
	std::vector<BodyPart> mBodyParts;
	WinterEngine::Physics::RigidBody mBodyAnchorRB;
	WinterEngine::Physics::CollisionShape mBodyAnchorShape;
};