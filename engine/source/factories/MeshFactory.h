#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include <fbxsdk.h>

#include "graphics/DirectX11/DXTypes.h"
#include "graphics/objects/Mesh.h"
#define PRIMITIVE_CUBE "cubeMesh"
#define PRIMITIVE_SPHERE "sphereMesh"


namespace drach
{
	class GraphicsEngine;
	class MeshFactory
	{
		friend class FBXContext;
	public:
		MeshFactory(GraphicsEngine& anEngine);
		Mesh* GetMesh(std::string aName);
	private:
		Mesh* LoadMesh(std::string aName);
		
		Mesh* GenerateCube();
		Mesh* GenerateSphere();
	private:
		Mesh* LoadMesh(fbxsdk::FbxMesh* aMesh, std::string aName, const float aSceneScale);
		const bool ParseVertices(GBuffer& aBuffer, std::vector<Vertex> someVertices);
		const bool ParseIndices(GBuffer& aBuffer, std::vector<uint32_t> someIndices);
	private:
		std::unordered_map<std::string, std::unique_ptr<Mesh>> myDatabase;
	private:
		GraphicsEngine* myGraphicsEngine;
	};
}