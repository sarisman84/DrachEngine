#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "graphics/DirectX11/DXTypes.h"
#define PRIMITIVE_CUBE "cubeMesh"
#define PRIMITIVE_SPHERE "sphereMesh"

namespace drach
{
	class Mesh;
	class GraphicsEngine;
	class MeshFactory
	{
	public:
		MeshFactory(GraphicsEngine& anEngine);
		Mesh* GetMesh(std::string aName);
	private:
		Mesh* LoadMesh(std::string aName);
		Mesh* GenerateCube();
		Mesh* GenerateSphere();
	private:
		const bool ParseVertices(GBuffer& aBuffer, std::vector<Vertex> someVertices);
		const bool ParseIndices(GBuffer& aBuffer, std::vector<uint32_t> someIndices);
	private:
		std::unordered_map<std::string, std::unique_ptr<Mesh>> myDatabase;
	private:
		GraphicsEngine* myGraphicsEngine;
	};
}