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
	void UpdateEnemyRotation();
	void NextTauntEvent();
	void CameraToSnakeEvent();
	void CameraToEnemyEvent();
	void CameraToActionShot();

	//Camera
	WinterEngine::Graphics::Camera mCamera;

	//Lighting
	WinterEngine::Graphics::DirectionalLight mDirectionalLight;
	WinterEngine::Graphics::StandardEffect mStandardEffect;

	//Scene State
	enum class SceneState
	{
		Gameplay,
		Animation
	};
	SceneState mCurrentSceneState = SceneState::Gameplay;
	float sceneTimer = 0.0f;

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

	//Final Enemy
	WinterEngine::Graphics::RenderGroup mFinalEnemy;
	WinterEngine::Graphics::Animator mFinalEnemyAnimator;

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

	//AnimationFrames
	float mEnemyAnimationTime = 0.0f;
	WinterEngine::Graphics::Animation mFinalEnemyAnimation;
	int enemyTauntNumber = 2;
	float mSnakeAnimationTime = 0.0f;
	WinterEngine::Graphics::Animation mSnakeAnimation;

	//Sound
	WinterEngine::Audio::SoundId mChompSoundId = 0;
	WinterEngine::Audio::SoundId mBennyHillId = 0;
	WinterEngine::Audio::SoundId mOneWingedId = 0;
};