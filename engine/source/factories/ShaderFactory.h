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
	struct InputStructure
	{
	public:
		void Add(std::string aName, DXGI_FORMAT&& aFormat);

		inline InputLayoutData& operator[](const size_t anIndex)
		{
			return myData[anIndex];
		}

		inline const bool IsPopulated() { return !myData.empty(); }
		inline const size_t DataSize() { return myData.size(); }
	private:
		std::vector<InputLayoutData> myData;
	};

	struct InputLayoutData
	{
		InputLayoutData(
			std::string aName, 
			DXGI_FORMAT&& aFormat, 
			size_t anInputSlot = 0,
			size_t anAlignmentOffset = 0xffffffff,
			D3D11_INPUT_CLASSIFICATION anInputSlotClassification = D3D11_INPUT_CLASSIFICATION(0),
			size_t anInstanceDataStepRate = 0) :
			myName(aName),
			myFormat(&aFormat),
			myInputSlot(anInputSlot),
			myAlignmentOffset(anAlignmentOffset),
			myInputSlotClass(&anInputSlotClassification),
			myInstanceDataStepRate(anInstanceDataStepRate)
		{

		}
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

		const bool AddShader(const std::string_view aFilePath, ShaderID* aVertexID = nullptr, ShaderID* aPixelID = nullptr);

		const ShaderID AddVertexShader(const std::string_view aFilePath);
		const ShaderID AddPixelShader(const std::string_view aFilePath);
		const ShaderID AddInputLayout(InputStructure aStructure, const ShaderID aVertexShader);

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