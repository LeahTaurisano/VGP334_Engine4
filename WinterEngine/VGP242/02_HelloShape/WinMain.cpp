#include <WinterEngine/Inc/WinterEngine.h>

#include "GameState.h"

using namespace WinterEngine;
using namespace WinterEngine::Graphics;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	App& myApp = WinterEngine::MainApp();
	myApp.AddState<TriangleState>("TriangleState");
	myApp.AddState<SquareState>("SquareState");
	myApp.AddState<StarState>("StarState");

	AppConfig config;
	config.appName = L"Hello Shapes";

	myApp.Run(config);
	return(0);
}