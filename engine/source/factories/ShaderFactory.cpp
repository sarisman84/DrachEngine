#include "ShaderFactory.h"
#include <d3d11.h> 
#include <d3d10.h>

#include "DirectXTex/DirectXTex/DirectXTex.h"
#include "graphics/GraphicsEngine.h"


#include "logging/Logger.h"

#pragma comment(lib, "d3dcompiler.lib")



drach::ShaderFactory::ShaderFactory(GraphicsEngine& anEngine) : myGraphicsEngine(anEngine)
{
	D3D11_APPEND_ALIGNED_ELEMENT;
	D3D11_INPUT_PER_VERTEX_DATA;
}

const ShaderID drach::ShaderFactory::AddVertexShader(const std::string_view aFilePath)
{
	GraphicsDevice& device = myGraphicsEngine.GetDevice();

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
	GraphicsDevice& device = myGraphicsEngine.GetDevice();

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
	static ShaderID id = 0;

	return false;
}

const bool drach::ShaderFactory::GetVertexShader(const ShaderID anID, VertexShader& aVertexShader)
{
	return false;
}

const bool drach::ShaderFactory::GetPixelShader(const ShaderID anID, PixelShader& aPixelShader)
{
	return false;
}

const bool drach::ShaderFactory::GetInputLayout(const ShaderID anID, InputLayout& anInputLayout)
{
	return false;
}
