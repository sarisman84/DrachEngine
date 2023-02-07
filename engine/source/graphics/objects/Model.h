#pragma once
#include "Mesh.h"
#include "Material.h"
namespace drach
{

	class Model
	{
	public:
		std::string myName;

	public:
		inline const std::vector<Mesh*> GetSubMeshes()const noexcept { return myMeshes; }
		inline const std::vector<Material> GetMaterials() const noexcept { return myMaterials; }
		inline const size_t GetSubMeshCount()  const noexcept { return myMeshes.size(); }
	private:
		std::vector<Material> myMaterials;
		std::vector<Mesh*> myMeshes;
	};

}