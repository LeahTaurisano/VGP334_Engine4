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
	void UpdateEnemyVisual();

	//Camera
	WinterEngine::Graphics::Camera mCamera;

	//Lighting
	WinterEngine::Graphics::DirectionalLight mDirectionalLight;
	WinterEngine::Graphics::StandardEffect mStandardEffect;

	//Ground
	WinterEngine::Graphics::RenderObject mGround;
	WinterEngine::Physics::RigidBody mGroundRB;
	WinterEngine::Physics::CollisionShape mGroundShape;
	
	//Enemy
	WinterEngine::Graphics::RenderGroup mEnemy;
	WinterEngine::Graphics::RenderObject mOrb;
	float mOrbRadius = 0;
	WinterEngine::Graphics::Animator mEnemyAnimator;
	Vector3 enemyStartPos = Vector3::Zero;
	Vector3 enemyTargetPos = Vector3::Zero;
	float enemySpeed = 5.0f;
	float currentMovementTime = 0.0f;

	//Snake
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

	//Particles
	WinterEngine::Graphics::ParticleSystemEffect mParticleSystemEffect;
	WinterEngine::Physics::ParticleSystem mParticleSystem;
};