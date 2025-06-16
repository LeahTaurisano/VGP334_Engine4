#include <WinterEngine/Inc/WinterEngine.h>

#include "GameState.h"
#include "EditTemplateState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	App& myApp = WinterEngine::MainApp();
	myApp.AddState<GameState>("GameState");
	myApp.AddState<GameState>("EditTemplateState");

	AppConfig config;
	config.appName = L"Hello GameObjectFactory";

	myApp.Run(config);
	return(0);
}