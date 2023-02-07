#pragma once
#include <string>
namespace drach
{
	class Material
	{
		friend class Renderer;
	public:
		std::string myName;
	private:
		uint32_t myPixelShader;
		uint32_t myVertexShader;
		uint32_t myInputLayout;
	};
}