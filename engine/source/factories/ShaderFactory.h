#pragma once
#include <unordered_map>
#include <vector>
#include <string>

#include "graphics/DirectX11/DXTypes.h"

typedef uint32_t ShaderID;
inline ShaderID nullshader = ShaderID(-1);


namespace drach
{
	class GraphicsEngine;

	struct ShaderData
	{
		ShaderID myVertexShader;
		ShaderID myPixelShader;
		ShaderID myInputLayout;
	};

	struct InputLayoutData
	{
		InputLayoutData() = default;
		std::string myName;
		DXGI_FORMAT* myFormat;
		size_t myInputSlot = 0;
		size_t myAlignmentOffset = 0xffffffff;
		D3D11_INPUT_CLASSIFICATION* myInputSlotClass;
		size_t myInstanceDataStepRate = 0;
	};

	class ShaderFactory
	{
	public:
		ShaderFactory(GraphicsEngine& anEngine);

		const ShaderID AddVertexShader(const std::string_view aFilePath);
		const ShaderID AddPixelShader(const std::string_view aFilePath);
		const ShaderID AddInputLayout(std::vector<InputLayoutData> someData, const ShaderID aVertexShader);

		const bool GetVertexShader(const ShaderID anID, VertexShader& aVertexShader);
		const bool GetPixelShader(const ShaderID anID, PixelShader& aPixelShader);
		const bool GetInputLayout(const ShaderID anID, InputLayout& anInputLayout);

	private:
		GraphicsEngine* myGraphicsEngine;
	private:
		std::unordered_map<ShaderID, Blob> myVertexData;
		std::unordered_map<ShaderID, VertexShader> myVertexShaders;
		std::unordered_map<ShaderID, PixelShader> myPixelShaders;
		std::unordered_map<ShaderID, InputLayout> myInputLayouts;
	};

}