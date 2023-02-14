#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <tuple>
#include "graphics/DirectX11/DXTypes.h"

#include "util/other/StringID.h"


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
		ShaderFactory& myShaderDatabase;
		StringID myID;
	};

	class ShaderFactory
	{
		friend class Shader;
	public:
		ShaderFactory(GraphicsEngine& anEngine);

	public:
		Shader GetShaderFromFile(std::string aFilePath, const ShaderType aType = ShaderType::All);
	private:
		HRESULT LoadInputLayout(Blob& someVertexData, InputLayout& anInputLayout);
	private:
		GraphicsEngine* myGraphicsEngine;
	private:
		std::unordered_map<StringID, std::tuple<VertexShader, PixelShader, InputLayout>, StringIDHash> myShaders;
	};

}