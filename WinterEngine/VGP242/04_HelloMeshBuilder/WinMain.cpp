#include <WinterEngine/Inc/WinterEngine.h>

#include "GameState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	App& myApp = WinterEngine::MainApp();
	myApp.AddState<CubeState>("CubeState");
	myApp.AddState<RectState>("RectState");
	myApp.AddState<PlaneState>("PlaneState");
	myApp.AddState<SphereState>("SphereState");
	myApp.AddState<CylinderState>("CylinderState");
	myApp.AddState<SkyboxState>("SkyboxState");
	myApp.AddState<SkysphereState>("SkysphereState");

	AppConfig config;
	config.appName = L"Hello Mesh Builder";

	myApp.Run(config);
	return(0);
}