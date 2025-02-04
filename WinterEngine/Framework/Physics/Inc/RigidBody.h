#pragma once

#include "PhysicsObject.h"

namespace WinterEngine::Physics
{
	class CollisionShape;

	class RigidBody final : public PhysicsObject
	{
	public:
		RigidBody() = default;
		~RigidBody() override;

		void Initialize(WinterEngine::Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass = 0.0f);
		void Terminate();

		void SetPosition(const WinterEngine::Math::Vector3& position);
		void SetVelocity(const WinterEngine::Math::Vector3& velocity);

		bool IsDynamic() const;

	private:
		void SyncWithGraphics() override;
		btRigidBody* GetRigidBody() override;

		btRigidBody* mRigidBody = nullptr;
		btDefaultMotionState* mMotionState = nullptr;
		float mMass = 0.0f;

		WinterEngine::Graphics::Transform* mGraphicsTransform = nullptr;
	};
}