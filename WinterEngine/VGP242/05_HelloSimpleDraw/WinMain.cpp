#include <WinterEngine/Inc/WinterEngine.h>

#include "GameState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	App& myApp = WinterEngine::MainApp();
	myApp.AddState<TransformState>("TransformState");
	myApp.AddState<SphereState>("SphereState");
	myApp.AddState<AABBState>("AABBState");
	myApp.AddState<AABBFilledState>("AABBFilledState");
	myApp.AddState<LinesState>("LinesState");

	AppConfig config;
	config.appName = L"Hello Simple Draw";

	myApp.Run(config);
	return(0);
}