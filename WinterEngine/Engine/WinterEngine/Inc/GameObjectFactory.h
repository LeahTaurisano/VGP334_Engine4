#pragma once


namespace WinterEngine
{
	class GameObject;
	class GameWorld;
	class Component;

	using CustomComponentCB = std::function<Component* (const std::string&, GameObject&)>;

	namespace GameObjectFactory
	{
		void SetCustomMake(CustomComponentCB cb);
		void SetCustomGet(CustomComponentCB cb);
		void Make(const std::filesystem::path& templatePath, GameObject& gameObject, GameWorld& gameWorld);
		void OverrideDeserialize(const rapidjson::Value& value, GameObject& gameObject);
		void SerializeGameObject(rapidjson::Document& doc, const rapidjson::Document& original, GameObject& gameObject);
	}
}