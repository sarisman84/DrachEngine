#pragma once
#include <vector>
#include <string>
#include <util/math/Vector3.h>

#include "graphics/DirectX11/DXTypes.h"
namespace drach
{
	struct Vertex
	{
		Vector3f myPosition;
		Vector2f myUV;
	};
	
	class Mesh
	{
		friend class Renderer;
		friend class MeshFactory;
	public:
		std::string myName;
	private:
		GBuffer myVertexBuffer;
		GBuffer myIndexBuffer;
		size_t myIndicesAmm;
	};
}