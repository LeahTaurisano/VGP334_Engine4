#pragma once

#include <WinterEngine/Inc/WinterEngine.h>

class EditTemplateState : public WinterEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

protected:

	WinterEngine::GameWorld mGameWorld;
};