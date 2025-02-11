#pragma once

//framework headers
#include <Math/Inc/WinterMath.h>
#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>

//bullet headers
#include <Bullet/btBulletCollisionCommon.h>
#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/BulletSoftBody/btSoftRigidDynamicsWorld.h>
#include <Bullet/BulletSoftBody/btSoftBodyHelpers.h>
#include <Bullet/BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <Bullet/BulletSoftBody/btSoftBodySolvers.h>

#define USE_SOFT_BODY //Disable if not using Soft Body

//helper function
template<class T>
inline void SafeDelete(T*& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

inline btVector3 TobtVector3(const WinterEngine::Math::Vector3 v)
{
	return btVector3(v.x, v.y, v.z);
}
inline WinterEngine::Math::Vector3 ToVector3(const btVector3& v)
{
	return {
		static_cast<float>(v.getX()),
		static_cast<float>(v.getY()),
		static_cast<float>(v.getZ())
	};
}

inline btQuaternion TobtQuaternion(const WinterEngine::Math::Quaternion q)
{
	return btQuaternion(q.x, q.y, q.z, q.w);
}
inline WinterEngine::Math::Quaternion ToQuaternion(const btQuaternion& q)
{
	return
	{
		static_cast<float>(q.getX()),
		static_cast<float>(q.getY()),
		static_cast<float>(q.getZ()),
		static_cast<float>(q.getW())
	};
}

inline WinterEngine::Color ToColor(const btVector3& c)
{
	return {
		static_cast<float>(c.getX()),
		static_cast<float>(c.getY()),
		static_cast<float>(c.getZ()),
		1.0f
	};
}

inline btTransform ConvertTobtTransform(const WinterEngine::Graphics::Transform& transform)
{
	return btTransform(TobtQuaternion(transform.rotation), TobtVector3(transform.position));
}