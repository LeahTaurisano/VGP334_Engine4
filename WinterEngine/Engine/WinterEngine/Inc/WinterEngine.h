#pragma once

#include "Common.h"

#include "App.h"
#include "AppState.h"
#include "Event.h"
#include "EventManager.h"

#include "SaveUtil.h"

//Game Object
#include "GameObject.h"
#include "TypeIds.h"
#include "GameObjectFactory.h"
#include "GameObjectHandle.h"

//Components
#include "Component.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "FPSCameraComponent.h"
#include "RenderObjectComponent.h"
#include "MeshComponent.h"
#include "ModelComponent.h"
#include "AnimatorComponent.h"
#include "RigidBodyComponent.h"
#include "SoundEffectComponent.h"
#include "SoundBankComponent.h"
#include "UIComponent.h"
#include "UITextComponent.h"
#include "UISpriteComponent.h"
#include "UIButtonComponent.h"

//Services
#include "Service.h"
#include "GameWorld.h"
#include "CameraService.h"
#include "RenderService.h"
#include "PhysicsService.h"
#include "UIRenderService.h"

namespace WinterEngine
{
	App& MainApp();
}