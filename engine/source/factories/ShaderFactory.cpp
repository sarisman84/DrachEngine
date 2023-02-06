#include "ShaderFactory.h"
#include <d3d11.h> 
#include <d3d10.h>

#include "DirectXTex/DirectXTex/DirectXTex.h"
#include "graphics/GraphicsEngine.h"


#include "logging/Logger.h"

#pragma comment(lib, "d3dcompiler.lib")



drach::ShaderFactory::ShaderFactory(GraphicsEngine& anEngine) : myGraphicsEngine(&anEngine)
{

}

const ShaderID drach::ShaderFactory::AddVertexShader(const std::string_view aFilePath)
{
	GraphicsDevice& device = myGraphicsEngine->GetDevice();

	static ShaderID id = 0;

	Blob data;



	std::wstring path = std::wstring(aFilePath.begin(), aFilePath.end());
	path += std::wstring(L".cso");
	HRESULT result = D3DReadFileToBlob(path.c_str(), &data);
	if (FAILED(result))
	{
		LOG_ERROR("Failed to read vertex shader file [" + std::string(aFilePath) + "]");
		return nullshader;
	}

	ShaderID cpy = id;


	ShaderID newID = cpy++;
	myVertexData[newID] = data;

	result = device->CreateVertexShader(data->GetBufferPointer(), data->GetBufferSize(), nullptr, &myVertexShaders[newID]);

	if (FAILED(result))
	{
		LOG_ERROR("Failed to create vertex shader! HRESULT: " + std::to_string(result));
		return nullshader;
	}

	id = cpy;

	return newID;
}

const ShaderID drach::ShaderFactory::AddPixelShader(const std::string_view aFilePath)
{
	GraphicsDevice& device = myGraphicsEngine->GetDevice();

	static ShaderID id = 0;

	Blob data;



	std::wstring path = std::wstring(aFilePath.begin(), aFilePath.end());
	path += std::wstring(L".cso");
	HRESULT result = D3DReadFileToBlob(path.c_str(), &data);
	if (FAILED(result))
	{
		LOG_ERROR("Failed to read pixel shader file [" + std::string(aFilePath) + "]");
		return nullshader;
	}

	ShaderID cpy = id;

	ShaderID newID = cpy++;
	result = device->CreatePixelShader(data->GetBufferPointer(), data->GetBufferSize(), nullptr, &myPixelShaders[newID]);

	if (FAILED(result))
	{
		LOG_ERROR("Failed to create pixel shader! HRESULT: " + std::to_string(result));
		return nullshader;
	}

	id = cpy;

	return newID;
}

const ShaderID drach::ShaderFactory::AddInputLayout(std::vector<InputLayoutData> someData, const ShaderID aVertexShader)
{
	GraphicsDevice& device = myGraphicsEngine->GetDevice();

	static ShaderID id = 0;

	if (someData.size() <= 0)
	{
		LOG_ERROR("Incoming vector InputLayoutData is invalid");
		return false;
	}

	if (myVertexData.count(aVertexShader) <= 0)
	{
		LOG_ERROR("Assigned VertexShaderID does not exist in the database.");
		return false;
	}


	if (aVertexShader == nullshader)
	{
		LOG_ERROR("Assigned VertexShaderID is invalid.");
		return false;
	}

	Blob& vertexData = myVertexData[aVertexShader];
	D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[someData.size()];
	for (size_t i = 0; i < someData.size(); i++)
	{
		auto& data = someData[i];
		layout[i] = { data.myName.c_str(), 0, *data.myFormat, (unsigned int)data.myInputSlot, (unsigned int)data.myAlignmentOffset, *data.myInputSlotClass, (unsigned int)data.myInstanceDataStepRate };
	}

	ShaderID cpy = id;
	ShaderID newID = cpy++;

	HRESULT result = device->CreateInputLayout(layout, someData.size(), vertexData->GetBufferPointer(), vertexData->GetBufferSize(), &myInputLayouts[newID]);
	if (FAILED(result))
	{
		LOG_ERROR("Failed to create input layout. HResult: " + std::to_string(result));
		return false;
	}

	return true;
}

const bool drach::ShaderFactory::GetVertexShader(const ShaderID anID, VertexShader& aVertexShader)
{
	if (myVertexShaders.count(anID) <= 0)
	{
		LOG_ERROR("Assigned VertexShaderID does not exist in the database.");
		return false;
	}


	aVertexShader = myVertexShaders[anID];

	return true;
}

const bool drach::ShaderFactory::GetPixelShader(const ShaderID anID, PixelShader& aPixelShader)
{
	if (myPixelShaders.count(anID) <= 0)
	{
		LOG_ERROR("Assigned PixelShaderID does not exist in the database.");
		return false;
	}


	aPixelShader = myPixelShaders[anID];

	return true;
}

const bool drach::ShaderFactory::GetInputLayout(const ShaderID anID, InputLayout& anInputLayout)
{
	if (myInputLayouts.count(anID) <= 0)
	{
		LOG_ERROR("Assigned InputLayoutID does not exist in the database.");
		return false;
	}


	anInputLayout = myInputLayouts[anID];

	return true;
}
