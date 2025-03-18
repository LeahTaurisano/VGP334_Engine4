#include "GameState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;
using namespace WinterEngine::Input;
using namespace WinterEngine::Audio;
using namespace WinterEngine::Physics;

void GameState::Initialize()
{
	srand(time(nullptr));

	//Camera
	mCamera.SetPosition({ 0.0f, 30.0f, -10.0f });
	mCamera.SetLookAt({0.0f, 0.0f, 0.0f});

	//Lighting
	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };

	//Standard Effect
	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	//Ground
	Mesh ground = MeshBuilder::CreateGroundPlane(30, 30, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureCache::Get()->LoadTexture("misc/concrete.jpg");
	mGroundShape.InitializeHull({ 15.0f, 0.5f, 15.0f }, { 0.0f, -0.5, 0.0f });
	mGroundRB.Initialize(mGround.transform, mGroundShape);

	//Enemy
	float randX = rand() % 30;
	float randZ = rand() % 30;
	enemyTargetPos = { randX - 15, 1.0f, randZ - 15 };
	mEnemy.Initialize(L"../../Assets/Models/Character03/CastleGuard.model", &mEnemyAnimator);
	ModelCache::Get()->AddAnimation(mEnemy.modelId, L"../../Assets/Models/Character03/Run.model");
	mEnemyAnimator.Initialize(mEnemy.modelId);
	mEnemyAnimator.PlayAnimation(1, true);
	mOrbRadius = 1.0f;
	Mesh orb = MeshBuilder::CreateSphere(10, 10, mOrbRadius);
	mOrb.meshBuffer.Initialize(orb);
	mOrb.diffuseMapId = TextureCache::Get()->LoadTexture("Sprites/blue.jpg");
	randX = rand() % 30;
	randZ = rand() % 30;
	mOrb.transform.position = { randX - 15, 1.0f, randZ - 15 };
	enemyStartPos = mOrb.transform.position;

	UpdateEnemyRotation();

	//Final Enemy
	mFinalEnemy.Initialize(L"../../Assets/Models/Character04/Paladin.model", &mFinalEnemyAnimator);
	ModelCache::Get()->AddAnimation(mFinalEnemy.modelId, L"../../Assets/Models/Character04/StrutWalking.model");
	ModelCache::Get()->AddAnimation(mFinalEnemy.modelId, L"../../Assets/Models/Character04/Situps.model");
	ModelCache::Get()->AddAnimation(mFinalEnemy.modelId, L"../../Assets/Models/Character04/Taunt.model");
	ModelCache::Get()->AddAnimation(mFinalEnemy.modelId, L"../../Assets/Models/Character04/TauntGesture.model");
	ModelCache::Get()->AddAnimation(mFinalEnemy.modelId, L"../../Assets/Models/Character04/DropKick.model");
	ModelCache::Get()->AddAnimation(mFinalEnemy.modelId, L"../../Assets/Models/Character04/GolfPrePutt.model");
	ModelCache::Get()->AddAnimation(mFinalEnemy.modelId, L"../../Assets/Models/Character04/GolfDrive.model");
	ModelCache::Get()->AddAnimation(mFinalEnemy.modelId, L"../../Assets/Models/Character04/Run.model");
	ModelCache::Get()->AddAnimation(mFinalEnemy.modelId, L"../../Assets/Models/Character04/Victory.model"); //9
	ModelCache::Get()->AddAnimation(mFinalEnemy.modelId, L"../../Assets/Models/Character04/Floating.model"); //10
	mFinalEnemyAnimator.Initialize(mFinalEnemy.modelId);
	mFinalEnemy.transform.position = { -10.0f, 0.0f, 0.0f };
	mFinalEnemy.transform.rotation = Quaternion::CreateFromAxisAngle(Vector3::YAxis, 270.0f * Constants::DegToRad);
	
	//Final Enemy Animation
	mFinalEnemyAnimation = AnimationBuilder()
		.AddEventKey(std::bind(&GameState::CameraToEnemyEvent, this), 0.0001f)
		.AddPositionKey({ -10.0f, 0.0f, 0.0f }, 0.0f)
		.AddPositionKey({ -5.0f, 0.0f, 0.0f }, 3.0f)
		.AddEventKey(std::bind(&GameState::CameraToSnakeEvent, this), 3.0f)
		.AddEventKey(std::bind(&GameState::FlipPauseBossMusic, this), 3.0f) //pause
		.AddEventKey(std::bind(&GameState::FlipPauseBossMusic, this), 6.0f) //play
		.AddEventKey(std::bind(&GameState::CameraToEnemyEvent, this), 6.0f)
		.AddEventKey(std::bind(&GameState::NextTauntEvent, this), 6.0f) //Situps
		.AddEventKey(std::bind(&GameState::CameraToSnakeEvent, this), 10.0f)
		.AddEventKey(std::bind(&GameState::FlipPauseBossMusic, this), 10.0f) //pause
		.AddEventKey(std::bind(&GameState::FlipPauseBossMusic, this), 13.0f) //play
		.AddEventKey(std::bind(&GameState::CameraToEnemyEvent, this), 13.0f)
		.AddEventKey(std::bind(&GameState::NextTauntEvent, this), 13.0f) //Taunt
		.AddEventKey(std::bind(&GameState::CameraToSnakeEvent, this), 17.0f)
		.AddEventKey(std::bind(&GameState::FlipPauseBossMusic, this), 17.0f) //pause
		.AddEventKey(std::bind(&GameState::FlipPauseBossMusic, this), 20.0f) //play
		.AddEventKey(std::bind(&GameState::CameraToEnemyEvent, this), 20.0f)
		.AddEventKey(std::bind(&GameState::NextTauntEvent, this), 20.0f) //Taunt Gesture
		.AddEventKey(std::bind(&GameState::CameraToSnakeEvent, this), 22.0f)
		.AddEventKey(std::bind(&GameState::FlipPauseBossMusic, this), 22.0f) //pause
		.AddEventKey(std::bind(&GameState::FlipPauseBossMusic, this), 25.0f) //play
		.AddEventKey(std::bind(&GameState::CameraToEnemyEvent, this), 25.0f)
		.AddEventKey(std::bind(&GameState::NextTauntEvent, this), 25.0f) //Drop Kick
		.AddEventKey(std::bind(&GameState::CameraToSnakeEvent, this), 27.5f)
		.AddEventKey(std::bind(&GameState::FlipPauseBossMusic, this), 27.0f) //pause
		.AddEventKey(std::bind(&GameState::FlipPauseBossMusic, this), 31.0f) //play
		.AddEventKey(std::bind(&GameState::CameraToEnemyEvent, this), 31.0f)
		.AddEventKey(std::bind(&GameState::NextTauntEvent, this), 31.0f) //Golf Pre Putt
		.AddEventKey(std::bind(&GameState::CameraToSnakeEvent, this), 41.0f)
		.AddEventKey(std::bind(&GameState::FlipPauseBossMusic, this), 41.0f) //pause
		.AddEventKey(std::bind(&GameState::FlipPauseBossMusic, this), 44.0f) //play
		.AddEventKey(std::bind(&GameState::CameraToEnemyEvent, this), 44.0f)
		.AddEventKey(std::bind(&GameState::NextTauntEvent, this), 44.0f) //Golf Drive
		.AddEventKey(std::bind(&GameState::CameraToSnakeEvent, this), 47.0f)
		.AddEventKey(std::bind(&GameState::FlipPauseBossMusic, this), 47.0f) //pause
		.AddEventKey(std::bind(&GameState::FlipPauseBossMusic, this), 50.0f) //play
		.AddEventKey(std::bind(&GameState::CameraToActionShot, this), 50.0f)
		.AddPositionKey({ -5.0f, 0.0f, 0.0f }, 50.0f)
		.AddEventKey(std::bind(&GameState::NextTauntEvent, this), 50.0f) //Run
		.AddPositionKey({ -0.2f, 0.0f, 0.0f }, 52.0f)
		.AddEventKey(std::bind(&GameState::TransitionToEndEvent, this), 52.0f)
		.AddPositionKey({ -20.0f, 10.0f, 0.0f }, 54.0f)
		.Build();

	//Snake
	numSegments = 20;
	activeSegments = 1;
	float maxSphereSize = 1.0f;
	float minSphereSize = 0.25f;
	for (uint32_t i = 0; i < numSegments; ++i)
	{
		const float t = static_cast<float>(i) / static_cast<float>(numSegments - 1);
		float sphereSize = Math::Lerp(maxSphereSize, minSphereSize, t);
		Mesh sphere = MeshBuilder::CreateSphere(30, 30, sphereSize);
		BodyPart& newPart = mBodyParts.emplace_back();
		newPart.segment.meshBuffer.Initialize(sphere);
		newPart.segment.diffuseMapId = TextureCache::Get()->LoadTexture("Sprites/green.jpg");
		newPart.range = sphereSize;
		newPart.isActive = static_cast<int>(i) < activeSegments ? true : false;
			
	}
	mBodyAnchorShape.InitializeSphere(maxSphereSize);
	mBodyAnchorRB.Initialize(mBodyParts[0].segment.transform, mBodyAnchorShape, 1.0f);

	//Snake Animation
	mSnakeAnimation = AnimationBuilder()
		.AddPositionKey({ 5.0f, 1.0f, 0.0f }, 0.0f)
		.AddPositionKey({ 5.0f, 1.0f, 0.0f }, 50.0f)
		.AddPositionKey({ 0.2f, 1.0f, 0.0f }, 52.0f)
		.AddPositionKey({ 20.0f, 10.0f, 0.0f }, 54.0f)
		.Build();

	//Particles
	mParticleSystemEffect.Initialize();
	mParticleSystemEffect.SetCamera(mCamera);

	ParticleSystemInfo particleInfo;
	particleInfo.textureId = TextureCache::Get()->LoadTexture("sprites/explosion.png");
	particleInfo.maxParticles = 100;
	particleInfo.particlesPerEmit = { 10, 15 };
	particleInfo.delay = 0.0f;
	particleInfo.lifeTime = 0.0f;
	particleInfo.timeBetweenEmit = { 0.1f, 0.2f };
	particleInfo.spawnAngle = { -30.0f, 30.0f };
	particleInfo.spawnSpeed = { 1.0f, 3.0f };
	particleInfo.spawnLifetime = { 0.5f, 2.0f };
	particleInfo.spawnDirection = Math::Vector3::YAxis;
	particleInfo.spawnPosition = Math::Vector3::Zero;
	particleInfo.startScale = { Math::Vector3::One, Math::Vector3::One };
	particleInfo.endScale = { Math::Vector3::One, Math::Vector3::One };
	particleInfo.startColor = { Colors::DarkRed, Colors::Red };
	particleInfo.endColor = { Colors::Red, Colors::PaleVioletRed };
	mParticleSystem.Initialize(particleInfo);

	//Sound
	mChompSoundId = SoundEffectManager::Get()->Load("CartoonChompSoundEffect.wav");
	mBennyHillId = SoundEffectManager::Get()->Load("BennyHillTheme.wav");
	mOneWingedId = SoundEffectManager::Get()->Load("OneWingedAngel.wav");
	SoundEffectManager::Get()->Play(mBennyHillId);

}
void GameState::Terminate()
{
	mParticleSystem.Terminate();
	for (auto& part : mBodyParts)
	{
		part.segment.Terminate();
	}
	mBodyAnchorRB.Terminate();
	mBodyAnchorShape.Terminate();
	mOrb.Terminate();
	mFinalEnemy.Terminate();
	mEnemy.Terminate();
	mGroundRB.Terminate();
	mGroundShape.Terminate();
	mGround.Terminate();
	mStandardEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
	InputSystem* input = InputSystem::Get();

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

	sceneTimer += deltaTime;
	if (mCurrentSceneState == SceneState::Gameplay)
	{
		if (sceneTimer > snakeGameDuration) //Scene Transition to Animation Portion
		{
			mBodyAnchorRB.SetVelocity(Vector3::Zero);
			mBodyAnchorRB.SetPosition({ 5.0f, 1.0f, 0.0f });
			mCurrentSceneState = SceneState::Animation;
			mFinalEnemyAnimator.PlayAnimation(1, true);
			mCamera.SetPosition({ 0.0f, 1.0f, -2.0f });
			SoundEffectManager::Get()->Stop(mBennyHillId);
			SoundEffectManager::Get()->Play(mOneWingedId);
		}
		const float speed = 10.0f;
		Vector3 velocity = Vector3::Zero;                                                 
		if (input->IsKeyDown(KeyCode::UP))
		{
			velocity.z = 1.0f;
		}
		else if (input->IsKeyDown(KeyCode::DOWN))
		{
			velocity.z = -1.0f;
		}
		if (input->IsKeyDown(KeyCode::RIGHT))
		{
			velocity.x = 1.0f;
		}
		else if (input->IsKeyDown(KeyCode::LEFT))
		{
			velocity.x = -1.0f;
		}
		if (MagnitudeSqr(velocity) > 0.0f)
		{
			velocity = Normalize(velocity) * speed;
		}
		mBodyAnchorRB.SetVelocity(velocity);

		currentMovementTime += deltaTime;
		mOrb.transform.position = Lerp(enemyStartPos, enemyTargetPos, Clamp(currentMovementTime / (Magnitude(enemyTargetPos - enemyStartPos) / enemySpeed), 0.0f, 1.0f));

		if (MagnitudeSqr(mOrb.transform.position - enemyTargetPos) < 0.5f)
		{
			currentMovementTime = 0.0f;
			float randX = rand() % 30;
			float randZ = rand() % 30;
			Vector3 targetPos = { randX - 15, 1.0f, randZ - 15 };
			while (MagnitudeSqr(mOrb.transform.position - targetPos) < 0.5f)
			{
				targetPos.x = (rand() % 30) - 15.0f;
				targetPos.z = (rand() % 30) - 15.0f;
			}
			enemyTargetPos = targetPos;
			enemyStartPos = mOrb.transform.position;

			UpdateEnemyRotation();
		}

		if (MagnitudeSqr(mOrb.transform.position - mBodyParts[0].segment.transform.position) < (mOrbRadius + mBodyParts[0].range) * (mOrbRadius + mBodyParts[0].range))
		{
			mParticleSystem.SetPosition(mOrb.transform.position);
			mParticleSystem.SpawnParticles();
			float randX = rand() % 30;
			float randZ = rand() % 30;
			Vector3 targetPos = { randX - 15, 1.0f, randZ - 15 };
			while (MagnitudeSqr(targetPos - mBodyParts[0].segment.transform.position) < (mOrbRadius + mBodyParts[0].range) * (mOrbRadius + mBodyParts[0].range))
			{
				targetPos.x = (rand() % 30) - 15.0f;
				targetPos.z = (rand() % 30) - 15.0f;
			}
			mOrb.transform.position = targetPos;
			enemyStartPos = targetPos;
			++activeSegments;
			SoundEffectManager::Get()->Play(mChompSoundId);
			UpdateActiveSegments();
			enemySpeed += 1;
			UpdateEnemyRotation();
		}
		mEnemy.transform = mOrb.transform;

		mParticleSystem.Update(deltaTime);
		mEnemyAnimator.Update(deltaTime);
	}
	else if (mCurrentSceneState == SceneState::Animation)
	{
		if (mFinalEnemyAnimation.GetDuration() > 0.0f)
		{
			float prevTime = mEnemyAnimationTime;
			mEnemyAnimationTime += deltaTime;
			mFinalEnemyAnimation.PlayEvents(prevTime, mEnemyAnimationTime);
			mFinalEnemy.transform.position = mFinalEnemyAnimation.GetTransform(mEnemyAnimationTime).position;
		}
		mFinalEnemyAnimator.Update(deltaTime);

		if (mSnakeAnimation.GetDuration() > 0.0f)
		{
			float prevTime = mSnakeAnimationTime;
			mSnakeAnimationTime += deltaTime;
			mBodyAnchorRB.SetPosition(mSnakeAnimation.GetTransform(mSnakeAnimationTime).position);
		}
	}
	else
	{
		if (mFinalEnemyAnimation.GetDuration() > 0.0f && snakeVictory)
		{
			float prevTime = mEnemyAnimationTime;
			mEnemyAnimationTime += deltaTime;
			mFinalEnemyAnimation.PlayEvents(prevTime, mEnemyAnimationTime);
			mFinalEnemy.transform.position = mFinalEnemyAnimation.GetTransform(mEnemyAnimationTime).position;
		}
		mFinalEnemyAnimator.Update(deltaTime);

		if (mSnakeAnimation.GetDuration() > 0.0f && !snakeVictory)
		{
			float prevTime = mSnakeAnimationTime;
			mSnakeAnimationTime += deltaTime;
			mBodyAnchorRB.SetPosition(mSnakeAnimation.GetTransform(mSnakeAnimationTime).position);
		}
	}
}

void GameState::Render()
{
	for (size_t i = 1; i < mBodyParts.size(); ++i)
	{
		BodyPart& part = mBodyParts[i];
		if (part.isActive)
		{
			BodyPart& prevPart = mBodyParts[i - 1];
			Vector3 dir = part.segment.transform.position - prevPart.segment.transform.position;
			if (MagnitudeSqr(dir) > 0)
			{
				dir = Normalize(dir);
			}
			else
			{
				dir = Vector3::ZAxis;
			}
			if (mCurrentSceneState == SceneState::Animation)
			{
				dir = Vector3::XAxis;
			}
			part.segment.transform.position = prevPart.segment.transform.position + (dir * prevPart.range);
		}
	}

	mStandardEffect.Begin();
		for (auto& part : mBodyParts)
		{
			if (part.isActive)
			{
				mStandardEffect.Render(part.segment);
			}
		}
		mStandardEffect.Render(mGround);
		if (mCurrentSceneState == SceneState::Gameplay)
		{
			mStandardEffect.Render(mEnemy);
		}
		else
		{
			mStandardEffect.Render(mFinalEnemy);
		}
	mStandardEffect.End();

	mParticleSystemEffect.Begin();
		mParticleSystem.Render(mParticleSystemEffect);
	mParticleSystemEffect.End();
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
	if (ImGui::CollapsingHeader("Segments", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragInt("Count", &activeSegments, 1, 1, numSegments))
		{
			UpdateActiveSegments();
		}
	}
	ImGui::End();
}

void GameState::UpdateActiveSegments()
{
	for (int i = 1; i < numSegments; ++i)
	{
		if (i < activeSegments)
		{
			mBodyParts[i].isActive = true;
		}
		else
		{
			mBodyParts[i].isActive = false;
		}
	}
}

void GameState::UpdateEnemyRotation()
{
	Vector3 l = Normalize(enemyStartPos - enemyTargetPos);
	Vector3 r = Normalize(Math::Cross(Math::Vector3::YAxis, l));
	Vector3 u = Normalize(Math::Cross(l, r));

	Matrix4 rotationMatrix =
	{
		r.x, r.y, r.z, 0.0f,
		u.x, u.y, u.z, 0.0f,
		l.x, l.y, l.z, 0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	Quaternion rotation = Quaternion::CreateFromRotationMatrix(rotationMatrix);
	mOrb.transform.rotation = rotation;
}

void GameState::NextTauntEvent()
{
	mFinalEnemyAnimator.PlayAnimation(enemyTauntNumber, true);
	++enemyTauntNumber;
}

void GameState::CameraToSnakeEvent()
{
	mCamera.SetLookAt(mBodyParts[0].segment.transform.position);
}

void GameState::CameraToEnemyEvent()
{
	mCamera.SetLookAt(mFinalEnemy.transform.position);
}

void GameState::CameraToActionShot()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -8.0f });
	mCamera.SetLookAt({ 0.0f, 1.0f, 0.0f });
}

void GameState::TransitionToEndEvent()
{
	mCurrentSceneState = SceneState::End;
	snakeVictory = activeSegments > 14;
	if (snakeVictory)
	{
		mFinalEnemyAnimator.PlayAnimation(10, true);
	}
	else
	{
		mFinalEnemyAnimator.PlayAnimation(9, true);
	}
}

void GameState::FlipPauseBossMusic()
{
	if (bossMusicPaused)
	{
		SoundEffectManager::Get()->Resume(mOneWingedId);
	}
	else
	{
		SoundEffectManager::Get()->Pause(mOneWingedId);
	}
	bossMusicPaused = !bossMusicPaused;
}

