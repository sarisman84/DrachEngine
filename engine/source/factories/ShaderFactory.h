#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <tuple>
#include "graphics/DirectX11/DXTypes.h"

#include "util/other/StringID.h"

namespace drach
{
	class Shader;
}
typedef std::unordered_map<drach::StringID, std::tuple<VertexShader, PixelShader, InputLayout>, drach::StringIDHash> ShaderLibrary;
typedef std::vector<drach::Shader> ShaderDataSet;
namespace drach
{
	enum class ShaderType : unsigned char
	{
		VertexShader, PixelShader, InputLayout, All
	};


	class GraphicsEngine;

	class ShaderFactory;
	struct Shader
	{
		Shader();
		Shader(StringID anID, ShaderFactory& aFactory);

		void Bind(GraphicsEngine& anEngine);

		PixelShader& GetPixelShader();
		VertexShader& GetVertexShader();
		InputLayout& GetInputLayout();

		inline const StringID GetID()
		{
			return myID;
		}

	private:
		ShaderFactory* myShaderDatabase;
		StringID myID;
	};

	class ShaderFactory
	{
		friend class Shader;
	public:
		ShaderFactory();
		ShaderFactory(GraphicsEngine& anEngine);

	public:
		Shader GetShaderFromFile(std::string aFilePath, const ShaderType aType = ShaderType::All);
		
		ShaderDataSet GetShaders();
	private:
		HRESULT LoadInputLayout(Blob& someVertexData, InputLayout& anInputLayout);
	private:
		GraphicsEngine* myGraphicsEngine;
	private:
		ShaderLibrary myShaders;
	};

}