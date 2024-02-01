#pragma once

#include <WinterEngine/Inc/WinterEngine.h>

class GameState : public WinterEngine::AppState
{
public:
	void Initialize();
	void Terminate();

	void Update(float deltaTime);

private:
};