#pragma once
#include "fbxsdk.h"
#include <fbxsdk/core/fbxmanager.h>
#include <filesystem>
namespace drach
{
	class MeshFactory;

	class FBXContext
	{
	public:
		FBXContext(MeshFactory& aMeshFactory, const char* aFile);
		~FBXContext();

		void GetScene(FbxNode* aNode = nullptr);
		inline const std::string GetFileName() noexcept { return myFile.filename().string(); }


		constexpr bool IsValid() const noexcept { return myFBXManager && myFBXScene; }
		constexpr float SceneScale() const noexcept { return mySceneScale; }
	private:
		bool InitializeFBX();
		void LoadFBXFromFile(const char* aFile);

		void GetMesh(FbxNode* aNode);
		void GetLODGroup(FbxNode* aNode);

	private:
		std::filesystem::path myFile;
		FbxManager* myFBXManager{ nullptr };
		FbxScene* myFBXScene{ nullptr };
		float mySceneScale{ 1.0f };
		MeshFactory& myMeshFactory;
	};
}