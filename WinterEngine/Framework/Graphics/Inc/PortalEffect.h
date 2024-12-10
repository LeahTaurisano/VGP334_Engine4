#pragma once

#include "Camera.h"
#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "RenderTarget.h"
#include "Sampler.h"

namespace WinterEngine::Graphics
{
	class Camera;
	class RenderObject;
	class RenderGroup;
	class StandardEffect;

	class PortalEffect
	{
	public:
		void Initialize();
		void Terminate();

		void Begin();
		void Render(const RenderObject& renderObject);
		void End();

		void BeginPortalImageRender();
		void PortalImageRender(const RenderObject& renderObject);
		void PortalImageRender(const RenderGroup& renderGroup);
		void EndPortalImageRender();

		void DebugUI();

		void SetStandardEffect(StandardEffect& standardEffect);

		const Camera& GetPortalCamera() const;

		void LinkPortal(const PortalEffect& linkPortal);

		void SetGameCamera(const Camera& gameCamera);

		void SetPortalObject(RenderObject& renderObject);

	private:
		void UpdatePortalCamera();

		struct TransformData
		{
			Math::Matrix4 wvp;
		};

		using TransformBuffer = TypedConstantBuffer<TransformData>;
		TransformBuffer mTransformBuffer;

		VertexShader mVertexShader;
		PixelShader mPixelShader;

		Camera mPortalCamera;
		const Camera* mLinkedPortalCamera;

		RenderTarget mPortalRenderTarget;
		Sampler mSampler;

		const Camera* mGameCamera;
		StandardEffect* mStandardEffect;

		RenderObject* mPortalObject;
		float mSize = 100.0f;
	};
}