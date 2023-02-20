#include "precompile-header/coreIncludes.h"
#include "ShaderFactory.h"


#include "DirectXTex/DirectXTex/DirectXTex.h"
#include "graphics/GraphicsEngine.h"


#include "logging/Logger.h"


//Parses in reflection information to DXGI_FORMAT values for Input Layout.
DXGI_FORMAT GetDXGIFormat(const D3D11_SIGNATURE_PARAMETER_DESC& desc)
{
	switch (desc.Mask)
	{
	case 1: //The format contains one element
		switch (desc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
			LOG("Format found to be unsigned int of 1 value");
			return DXGI_FORMAT_R32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:
			LOG("Format found to be signed int of 1 value");
			return DXGI_FORMAT_R32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			LOG("Format found to be float of 1 value");
			return DXGI_FORMAT_R32_FLOAT;
		default:
			break;
		}
		break;
	case 3: //The format contains two elements
		switch (desc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
			LOG("Format found to be unsigned int of 2 values");
			return DXGI_FORMAT_R32G32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:
			LOG("Format found to be signed int of 2 values");
			return DXGI_FORMAT_R32G32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			LOG("Format found to be float of 2 values");
			return DXGI_FORMAT_R32G32_FLOAT;
		default:
			break;
		}
		break;

	case 7: //The format contains three elements
		switch (desc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
			LOG("Format found to be unsigned int of 3 values");
			return DXGI_FORMAT_R32G32B32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:
			LOG("Format found to be signed int of 3 values");
			return DXGI_FORMAT_R32G32B32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			LOG("Format found to be float of 3 values");
			return DXGI_FORMAT_R32G32B32_FLOAT;
		default:
			break;
		}
		break;

	case 15: //The format contains four elements
		switch (desc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
			LOG("Format found to be unsigned int of 4 values");
			return DXGI_FORMAT_R32G32B32A32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:
			LOG("Format found to be signed int of 4 values");
			return DXGI_FORMAT_R32G32B32A32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			LOG("Format found to be float of 4 values");
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
		default:
			break;
		}
		break;

	default:
		break;
	}

	LOG_ERROR("Could not parse format from the above information: " + std::to_string(desc.Mask));
	return DXGI_FORMAT_UNKNOWN;
}


drach::ShaderFactory::ShaderFactory() = default;

drach::ShaderFactory::ShaderFactory(drach::GraphicsEngine& anEngine) : myGraphicsEngine(&anEngine)
{

}

drach::Shader drach::ShaderFactory::GetShaderFromFile(std::string aFileName, const ShaderType aType)
{
	if (aFileName.empty())
		return Shader(StringID());

	//Then hash it with a value for comparison
	StringID id(aFileName);

	//Check if we already have the value in our database. If we do, fetch the data.
	if (myShaders.count(id) > 0)
	{
		return Shader(id);
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
		return Shader(id);
	}
	LOG("Read File: " + vsPath.string());
	result = D3DReadFileToBlob(psPath.wstring().c_str(), &pixelData);
	if (FAILED(result))
	{
		LOG_ERROR("Failed to read pixel shader file: " + psPath.string() + ".");
		return Shader(id);
	}
	LOG("Read File: " + psPath.string());
	result = context->CreateVertexShader(vertexData->GetBufferPointer(), vertexData->GetBufferSize(), NULL, &vs);
	if (FAILED(result))
	{
		LOG_ERROR("Failed to create vertex shader from file: " + vsPath.string() + ".");
		return Shader(id);
	}
	LOG("Created Vertex Shader: " + vsPath.string());
	result = context->CreatePixelShader(pixelData->GetBufferPointer(), pixelData->GetBufferSize(), NULL, &ps);
	if (FAILED(result))
	{
		LOG_ERROR("Failed to read pixel shader from file: " + psPath.string() + ".");
		return Shader(id);
	}
	LOG("Created Pixel Shader: " + psPath.string());
	result = LoadInputLayout(vertexData, il);
	if (FAILED(result))
	{
		LOG_ERROR("Failed to load input layout from vertex file: " + vsPath.string());
		return Shader(id);
	}
	LOG("Parsed Vertex Shader Input Layout: " + vsPath.string());
	//Finally, store the data and the id into the database.
	myShaders[id] = std::make_tuple(vs, ps, il);




	LOG("Initialized Shader: " + aFileName);
	//Whenever or not i created or fetch the data, return the shader struct with an id and this factory as a result.
	return Shader(id);
}

ShaderDataSet drach::ShaderFactory::GetShaders()
{
	static ShaderDataSet result;
	result.clear();

	for (auto& shader : myShaders)
	{
		result.push_back(Shader(shader.first));
	}

	return result;
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

		std::string wName = paramDesc.SemanticName;
		LOG("Element Found: " + wName);
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


drach::Shader::Shader() = default;

drach::Shader::Shader(StringID anID)
	:myID(anID)
{
}

void drach::Shader::Bind(GraphicsEngine& anEngine, ShaderFactory& aFactory)
{
	GDContext context = anEngine.GetContext();
	context->IASetInputLayout(GetInputLayout(aFactory).Get());
	context->VSSetShader(GetVertexShader(aFactory).Get(), nullptr, 0);
	context->PSSetShader(GetPixelShader(aFactory).Get(), nullptr, 0);
	

}

PixelShader& drach::Shader::GetPixelShader(ShaderFactory& aFactory)
{
	return std::get<PixelShader>(aFactory.myShaders[myID]);
}

VertexShader& drach::Shader::GetVertexShader(ShaderFactory& aFactory)
{
	return std::get<VertexShader>(aFactory.myShaders[myID]);
}

InputLayout& drach::Shader::GetInputLayout(ShaderFactory& aFactory)
{
	return std::get<InputLayout>(aFactory.myShaders[myID]);
}
