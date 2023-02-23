#include "FBXImporter.h"

drach::FBXImporter::FBXImporter()
{
	mySDKManager = FbxManager::Create();

	FbxImporter* importer = FbxImporter::Create(mySDKManager, "");
	importer;
	/*if (!importer->Initialize("path/to/my/fbx/file.fbx", -1, mySDKManager->GetIOSettings()))
	{
		return;
	}*/
}
