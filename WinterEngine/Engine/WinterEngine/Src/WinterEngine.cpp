#include "Precompile.h"
#include "WinterEngine.h"

WinterEngine::App& WinterEngine::MainApp()
{
	static App sApp;
	return sApp;
}