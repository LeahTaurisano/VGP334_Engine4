#pragma once

#include "Common.h"

#include "App.h"
#include "AppState.h"
#include "Event.h"
#include "EventManager.h"

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

//Services
#include "Service.h"
#include "GameWorld.h"
#include "CameraService.h"
#include "RenderService.h"

namespace WinterEngine
{
	App& MainApp();
}