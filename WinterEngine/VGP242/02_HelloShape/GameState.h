#pragma once

#include <WinterEngine/Inc/WinterEngine.h>

class GameState : public WinterEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	virtual void CreateShape() {};
	struct Vertex
	{
		WinterEngine::Math::Vector3 position;
		WinterEngine::Color color;
	};

	using Vertices = std::vector<Vertex>;
	Vertices mVertices;
	ID3D11Buffer* mVertexBuffer = nullptr;
	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11InputLayout* mInputLayout = nullptr;
	ID3D11PixelShader* mPixelShader = nullptr;
};

class TriangleState : public GameState
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};

class SquareState : public GameState
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};