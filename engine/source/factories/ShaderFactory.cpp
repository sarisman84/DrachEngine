#include "ShaderFactory.h"
#include <d3d11.h> 
#include <d3d10.h>
#include <d3d11shader.h>
#include <filesystem>

#include "DirectXTex/DirectXTex/DirectXTex.h"
#include "graphics/GraphicsEngine.h"


#include "logging/Logger.h"

#pragma comment(lib, "d3dcompiler.lib")


DXGI_FORMAT GetDXGIFormat(const D3D11_SIGNATURE_PARAMETER_DESC& desc)
{
	switch (desc.Mask)
	{
	case 1:
		switch (desc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
			return DXGI_FORMAT_R32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:
			return DXGI_FORMAT_R32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			return DXGI_FORMAT_R32_FLOAT;
		default:
			break;
		}
		break;
	case 3:
		switch (desc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
			return DXGI_FORMAT_R32G32B32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:
			return DXGI_FORMAT_R32G32B32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			return DXGI_FORMAT_R32G32B32_FLOAT;
		default:
			break;
		}
		break;
	case 7:
		switch (desc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
			return DXGI_FORMAT_R32G32B32A32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:
			return DXGI_FORMAT_R32G32B32A32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return DXGI_FORMAT_UNKNOWN;
}


drach::ShaderFactory::ShaderFactory(drach::GraphicsEngine& anEngine) : myGraphicsEngine(&anEngine)
{

}

drach::Shader drach::ShaderFactory::GetShaderFromFile(std::string aFileName, const ShaderType aType)
{


	//Then hash it with a value for comparison
	StringID id(aFileName);

	//Check if we already have the value in our database. If we do, fetch the data.
	if (myShaders.count(id) > 0)
	{
		LOG("Found Shader!");
		return Shader(id, *this);
	}
	GDevice context = myGraphicsEngine->GetDevice();

	//Otherwise, load the data from the file and create the appropiate information (shader stuff).
	VertexShader vs;
	PixelShader ps;
	InputLayout il;

	HRESULT result;

	Blob vertexData;
	Blob pixelData;


	std::filesystem::path vsPath("resources/shaders/" + aFileName + "_VS.cso");
	std::filesystem::path psPath("resources/shaders/" + aFileName + "_PS.cso");

	result = D3DReadFileToBlob(vsPath.wstring().c_str(), &vertexData);
	if (FAILED(result))
	{
		LOG_ERROR("Failed to read vertex shader file: " + vsPath.string() + ".");
		return Shader(id, *this);
	}
	LOG("Read File: " + vsPath.string());
	result = D3DReadFileToBlob(psPath.wstring().c_str(), &pixelData);
	if (FAILED(result))
	{
		LOG_ERROR("Failed to read pixel shader file: " + psPath.string() + ".");
		return Shader(id, *this);
	}
	LOG("Read File: " + psPath.string());
	result = context->CreateVertexShader(vertexData->GetBufferPointer(), vertexData->GetBufferSize(), NULL, &vs);
	if (FAILED(result))
	{
		LOG_ERROR("Failed to create vertex shader from file: " + vsPath.string() + ".");
		return Shader(id, *this);
	}
	LOG("Created Vertex Shader: " + vsPath.string());
	result = context->CreatePixelShader(pixelData->GetBufferPointer(), pixelData->GetBufferSize(), NULL, &ps);
	if (FAILED(result))
	{
		LOG_ERROR("Failed to read pixel shader from file: " + psPath.string() + ".");
		return Shader(id, *this);
	}
	LOG("Created Pixel Shader: " + psPath.string());
	result = LoadInputLayout(vertexData, il);
	if (FAILED(result))
	{
		LOG_ERROR("Failed to load input layout from vertex file: " + vsPath.string());
		return Shader(id, *this);
	}
	LOG("Parsed Vertex Shader Input Layout: " + vsPath.string());
	//Finally, store the data and the id into the database.
	myShaders[id] = std::make_tuple(vs, ps, il);




	LOG("Initialized Shader!");
	//Whenever or not i created or fetch the data, return the shader struct with an id and this factory as a result.
	return Shader(id, *this);
}

HRESULT drach::ShaderFactory::LoadInputLayout(Blob& someVertexData, InputLayout& anInputLayout)
{
	GDevice context = myGraphicsEngine->GetDevice();
	ID3D11ShaderReflection* reflection;
	HRESULT result = D3DReflect(someVertexData->GetBufferPointer(), someVertexData->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflection);
	if (FAILED(result))
	{
		return result;
	}
	D3D11_SHADER_DESC shaderInfo = {};
	reflection->GetDesc(&shaderInfo);

	D3D11_SIGNATURE_PARAMETER_DESC paramDesc = {};

	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;

	for (size_t i = 0; i < shaderInfo.InputParameters; i++)
	{
		reflection->GetInputParameterDesc(i, &paramDesc);

		D3D11_INPUT_ELEMENT_DESC elementDesc = {};
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.Format = GetDXGIFormat(paramDesc);
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		inputLayoutDesc.push_back(elementDesc);
	}

	result = context->CreateInputLayout(inputLayoutDesc.data(), inputLayoutDesc.size(),
		someVertexData->GetBufferPointer(), someVertexData->GetBufferSize(), &anInputLayout);
	if (FAILED(result))
	{
		return result;
	}

	return S_OK;
}


drach::Shader::Shader(StringID anID, ShaderFactory& aFactory)
	:myID(anID), myShaderDatabase(aFactory)
{
}

void drach::Shader::Bind(GraphicsEngine& anEngine)
{
	GDContext context = anEngine.GetContext();

	context->VSSetShader(GetVertexShader().Get(), nullptr, 0);
	context->PSSetShader(GetPixelShader().Get(), nullptr, 0);
	context->IASetInputLayout(GetInputLayout().Get());

}

PixelShader& drach::Shader::GetPixelShader()
{
	return std::get<PixelShader>(myShaderDatabase.myShaders[myID]);
}

VertexShader& drach::Shader::GetVertexShader()
{
	return std::get<VertexShader>(myShaderDatabase.myShaders[myID]);
}

InputLayout& drach::Shader::GetInputLayout()
{
	return std::get<InputLayout>(myShaderDatabase.myShaders[myID]);
}
