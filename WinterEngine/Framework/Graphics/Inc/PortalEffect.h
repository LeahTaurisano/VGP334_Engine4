#pragma once

#include "Camera.h"
#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "RenderTarget.h"

namespace WinterEngine::Graphics
{
	class Camera;
	class RenderObject;

	class PortalEffect
	{
	public:
		void Initialize();
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);

		void DebugUI();

		Camera GetPortalCamera();

	private:

		void LinkPortal(PortalEffect& linkPortal);

		struct TransformData
		{

		};

		using TransformBuffer = TypedConstantBuffer<TransformData>;
		TransformBuffer mTransformBuffer;

		VertexShader mVertexShader;
		PixelShader mPixelShader;

		Camera mPortalCamera;
		Camera mLinkedPortalCamera;

		RenderTarget mPortalRenderTarget;
	};
}