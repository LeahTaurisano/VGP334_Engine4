#pragma once

#include "Camera.h"
#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "RenderTarget.h"
#include "Sampler.h"
#include "MeshTypes.h"

namespace WinterEngine::Graphics
{
	class Camera;
	class RenderObject;
	class RenderGroup;
	class StandardEffect;

	class PortalEffect
	{
	public:
		void Initialize(const MeshPX& portalMesh);
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

		const RenderObject& GetPortalObject() const;

		void LinkPortal(const PortalEffect& linkPortal);
		void LinkPortalMesh(const MeshPX& meshPX);

		void SetGameCamera(const Camera& gameCamera);

		void SetPortalObject(RenderObject& renderObject);

		const MeshPX& GetPortalMesh() const { return mPortalMesh; }

	private:
		void UpdatePortalCamera();
		void UpdatePortalUV();

		struct TransformData
		{
			Math::Matrix4 wvp;
			Math::Vector3 portalPos;
			float padding = 0.0f;
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

		MeshPX mPortalMesh;
		const MeshPX* mLinkedPortalMesh;
		RenderObject* mPortalObject;
		const RenderObject* mLinkedPortalObject;
		float mSize = 100.0f;
	};
}