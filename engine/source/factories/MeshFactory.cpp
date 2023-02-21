#include "precompile-header/coreIncludes.h"
#include "MeshFactory.h"
#include "graphics/GraphicsEngine.h"
#include "graphics/objects/Mesh.h"

#include "logging/Logger.h"

#include <d3d11.h>
#include <d3d11shader.h>
drach::MeshFactory::MeshFactory(GraphicsEngine& anEngine)
	:myGraphicsEngine(&anEngine)
{
}

drach::Mesh* drach::MeshFactory::GetMesh(std::string aName)
{
	if (myDatabase.count(aName) <= 0)
		return LoadMesh(aName);

	return myDatabase[aName].get();
}

drach::Mesh* drach::MeshFactory::LoadMesh(std::string aName)
{
	if (aName == PRIMITIVE_CUBE)
	{
		return GenerateCube();
	}

	if (aName == PRIMITIVE_SPHERE)
	{
		return GenerateSphere();
	}

	return nullptr;
}

drach::Mesh* drach::MeshFactory::GenerateCube()
{
	LOG("Generating Primitive Cube!");
	std::unique_ptr<Mesh>& mesh = myDatabase[PRIMITIVE_CUBE] = std::make_unique<Mesh>();


	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;


	struct Face
	{
		std::array<Vertex, 4> myVertices;
		std::array<uint32_t, 6> myIndices;


		void Apply(std::vector<Vertex>& aVertex, std::vector<uint32_t>& someIndex)
		{
			for (size_t i = 0; i < 4; i++)
			{
				aVertex.push_back(myVertices[i]);
			}
			for (size_t i = 0; i < 4; i++)
			{
				someIndex.push_back(myIndices[i]);
			}
		}

	};


	for (size_t i = 0; i < 6; i++)
	{
		Face newFace;
		newFace.myVertices =
		{
			Vertex{Vector3f(-0.5f, -0.5f, 0.5f), Vector2f(0.0f, 0.0f)},
			Vertex{Vector3f(0.5f, 0.5f, 0.5f), Vector2f(0.0f, 0.0f)},
			Vertex{Vector3f(0.5f,-0.5f,0.5f), Vector2f(0.0f, 0.0f)},
			Vertex{Vector3f(-0.5f, 0.5f, 0.5f), Vector2f(0.0f, 0.0f)}
		};

		newFace.myIndices =
		{
			0,1,2,
			0,3,1
		};

		newFace.Apply(vertices, indices);

	}

	//vertices.push_back();
	//vertices.push_back();
	//vertices.push_back();

	if (!ParseVertices(mesh->myVertexBuffer, vertices))
		return nullptr;

	if (!ParseIndices(mesh->myIndexBuffer, indices))
		return nullptr;
	mesh->myIndicesAmm = indices.size();
	mesh->myName = "Cube";

	return mesh.get();
}

drach::Mesh* drach::MeshFactory::GenerateSphere()
{
	return nullptr;
}

const bool drach::MeshFactory::ParseVertices(GBuffer& aBuffer, std::vector<Vertex> someVertices)
{
	ID3D11Device* device = myGraphicsEngine->GetDevice();


	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(Vertex) * static_cast<UINT>(someVertices.size());
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0 };
	data.pSysMem = someVertices.data();

	HRESULT result = device->CreateBuffer(&desc, &data, &aBuffer);

	if (FAILED(result))
	{
		LOG_ERROR("Failed to create vertex buffer!");
		return false;
	}
	return true;
}

const bool drach::MeshFactory::ParseIndices(GBuffer& aBuffer, std::vector<uint32_t> someIndices)
{
	ID3D11Device* device = myGraphicsEngine->GetDevice();


	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(uint32_t) * static_cast<UINT>(someIndices.size());
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0 };
	data.pSysMem = someIndices.data();

	HRESULT result = device->CreateBuffer(&desc, &data, &aBuffer);

	if (FAILED(result))
	{
		LOG_ERROR("Failed to create index buffer!");
		return false;
	}
	return true;
}
