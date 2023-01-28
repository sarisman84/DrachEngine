#pragma once
#include "graphics/DirectX11/DXTypes.h"

namespace drach
{
	class Mesh;
	class Shader
	{
	public:
		//Applies this shader (pixel and vertex) to a target model
		void ApplyTo(Mesh& aModel);
	private:
		PixelShader myPixelShader;
		VertexShader myVertexShader;
	};
}