#include "precompile-header/coreIncludes.h"
#include "FBXImporter.h"
#include "factories/MeshFactory.h"
#include <cassert>
#include <thread>
#include <mutex>

#include "logging/Logger.h"


namespace
{
	std::mutex fbx_mutex{};
}


drach::FBXContext::FBXContext(MeshFactory& aMeshFactory, const char* aFile)
	:myMeshFactory(aMeshFactory)
{
	myFile = std::filesystem::path(aFile);
	std::lock_guard lock{ fbx_mutex };

	assert(aFile && "Invalid file path found!");


	LOG(std::string(aFile) + " " + (std::filesystem::exists(aFile) ? "Exists" : "Does not exist"));

	if (InitializeFBX())
	{
		LoadFBXFromFile(aFile);
		assert(IsValid() && "Current fbx context is invalid!");
	}
}

drach::FBXContext::~FBXContext()
{
	myFBXScene->Destroy();
	myFBXManager->Destroy();
}

void drach::FBXContext::GetScene(FbxNode* aRoot)
{
	assert(IsValid());

	if (!aRoot)
	{
		aRoot = myFBXScene->GetRootNode();
		if (!aRoot)return;
	}

	const int num_nodes{ aRoot->GetChildCount() };

	if (num_nodes <= 0) return;

	for (int i = 0; i < num_nodes; ++i)
	{
		FbxNode* node{ aRoot->GetChild(i) };
		if (!node) continue;


		if (node->GetMesh())
		{
			GetMesh(node);
		}
		else if (node->GetLodGroup())
		{
			GetLODGroup(node);
		}

		GetScene(node);
	}
}

bool drach::FBXContext::InitializeFBX()
{
	assert(!IsValid() && "Is already initialized!");

	myFBXManager = FbxManager::Create();
	if (!myFBXManager) return false;
	FbxIOSettings* ios{ FbxIOSettings::Create(myFBXManager, IOSROOT) };

	assert(ios && "Could not create ios!");

	myFBXManager->SetIOSettings(ios);
	return true;
}

void drach::FBXContext::LoadFBXFromFile(const char* aFile)
{
	assert(myFBXManager && !myFBXScene && "Already has a scene!");
	myFBXScene = FbxScene::Create(myFBXManager, "Importer Scene");
	if (!myFBXScene)
		return;

	FbxImporter* importer{ FbxImporter::Create(myFBXManager, "Importer") };
	if (!(importer &&
		importer->Initialize(aFile, -1, myFBXManager->GetIOSettings()) &&
		importer->Import(myFBXScene)))
	{
		LOG_ERROR(importer->GetStatus().GetErrorString());
		importer->Destroy();
		return;
	}


	importer->Destroy();

	mySceneScale = myFBXScene->GetGlobalSettings().GetSystemUnit().GetConversionFactorTo(FbxSystemUnit::m);


}

void drach::FBXContext::GetMesh(FbxNode* aNode)
{
	assert(aNode);

	if (FbxMesh * fbx_mesh{ aNode->GetMesh() })
	{
		if (fbx_mesh->RemoveBadPolygons() < 0.0f) return;

		FbxGeometryConverter gc{ myFBXManager };
		fbx_mesh = static_cast<FbxMesh*>(gc.Triangulate(fbx_mesh, true));
		if (!fbx_mesh || fbx_mesh->RemoveBadPolygons() < 0.0f) return;


		myMeshFactory.LoadMesh(fbx_mesh, myFile.string(), SceneScale());
	}
}

void drach::FBXContext::GetLODGroup(FbxNode* /*aNode*/)
{
}
