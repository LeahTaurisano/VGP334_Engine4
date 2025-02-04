#pragma once

namespace WinterEngine::Physics
{
	class CollisionShape final
	{
	public:
		CollisionShape() = default;
		~CollisionShape();

		void InitializeEmpty();
		void InitializeSphere(float radius);
		void InitializeCapsule(float radius, float height);
		void InitializeBox(const WinterEngine::Math::Vector3& halfExtents);
		void InitializeHull(const WinterEngine::Math::Vector3& halfExtents, const WinterEngine::Math::Vector3& origin);
		void Terminate();

	private:
		friend class RigidBody;
		btCollisionShape* mCollisionShape = nullptr;
	};
}