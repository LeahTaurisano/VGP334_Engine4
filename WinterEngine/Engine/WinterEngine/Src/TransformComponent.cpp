#include "Precompile.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "SaveUtil.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;

void TransformComponent::DebugUI()
{
	ImGui::DragFloat3("Position", &position.x, 0.1f);
	ImGui::DragFloat4("Rotation", &rotation.x, 0.01f);
	ImGui::DragFloat3("Scale", &scale.x, 0.1f);

	SimpleDraw::AddTransform(GetMatrix4());
}

void TransformComponent::Deserialize(const rapidjson::Value& value)
{
	SaveUtil::ReadVector3("Position", position, value);
	SaveUtil::ReadQuaternion("Rotation", rotation, value);
	SaveUtil::ReadVector3("Scale", scale, value);
	/*if (value.HasMember("Position"))
	{
		const auto& pos = value["Position"].GetArray();
		position.x = pos[0].GetFloat();
		position.y = pos[1].GetFloat();
		position.z = pos[2].GetFloat();
	}
	if (value.HasMember("Rotation"))
	{
		const auto& rot = value["Rotation"].GetArray();
		rotation.x = rot[0].GetFloat();
		rotation.y = rot[1].GetFloat();
		rotation.z = rot[2].GetFloat();
		rotation.w = rot[3].GetFloat();
	}
	if (value.HasMember("Scale"))
	{
		const auto& s = value["Scale"].GetArray();
		scale.x = s[0].GetFloat();
		scale.y = s[1].GetFloat();
		scale.z = s[2].GetFloat();
	}*/
}

void WinterEngine::TransformComponent::Serialize(rapidjson::Document& doc, rapidjson::Value& value, const rapidjson::Value& original)
{
	rapidjson::Value componentValue(rapidjson::kObjectType);
	SaveUtil::WriteVector3("Position", position, doc, componentValue);
	SaveUtil::WriteQuaternion("Rotation", rotation, doc, componentValue);
	SaveUtil::WriteVector3("Scale", scale, doc, componentValue);
	value.AddMember("TransformComponent", componentValue, doc.GetAllocator());
}

Transform TransformComponent::GetWorldTransform() const
{
	Transform worldTransform = *this;
	const GameObject* parent = GetOwner().GetParent();
	if (parent != nullptr)
	{
		Math::Matrix4 matWorld = GetMatrix4();
		while (parent != nullptr)
		{
			const TransformComponent* transformComponent = parent->GetComponent<TransformComponent>();
			ASSERT(transformComponent != nullptr, "TransformComponent: parernt does not have a transform");
			matWorld = matWorld * transformComponent->GetMatrix4();
			parent = parent->GetParent();
		}
		worldTransform.position = Math::GetTranslation(matWorld);
		worldTransform.scale = Math::GetScale(matWorld);
		worldTransform.rotation = Math::Quaternion::CreateFromRotationMatrix(matWorld);
	}
	return worldTransform;
}
