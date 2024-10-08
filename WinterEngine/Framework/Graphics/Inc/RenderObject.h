#pragma once

#include "MeshBuffer.h"
#include "TextureCache.h"
#include "Transform.h"

namespace WinterEngine::Graphics
{

	class RenderObject
	{
	public:
		void Terminate();

		Transform transform;
		MeshBuffer meshBuffer;
		TextureId diffuseTextureId;
	};
}