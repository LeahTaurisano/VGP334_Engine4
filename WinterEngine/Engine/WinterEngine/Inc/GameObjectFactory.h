#pragma once


namespace WinterEngine
{
	class GameObject;
	class GameWorld;

	namespace GameObjectFactory
	{
		void Make(const std::filesystem::path& templatePath, GameObject& gameObject, GameWorld& gameWorld);
	}
}