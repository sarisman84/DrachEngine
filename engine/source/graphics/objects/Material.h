#pragma once
#include <string>
#include "util/other/StringID.h"
namespace drach
{
	class Material
	{
		friend class Renderer;
	public:
		std::string myName;
	private:
		StringID myShaderID;
	};
}