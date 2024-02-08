#include <WinterEngine/Inc/WinterEngine.h>

#include "GameState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	App& myApp = WinterEngine::MainApp();
	myApp.AddState<GameState>("GameState");

	AppConfig config;
	config.appName = L"Hello Cube";

	myApp.Run(config);
	return(0);
}