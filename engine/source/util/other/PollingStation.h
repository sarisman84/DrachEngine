#pragma once
#include <unordered_map>
#include <memory>
#include "Object.h"
#include "TypeID.h"
namespace drach
{
	class ShaderFactory;
	class GraphicsEngine;
	class Renderer;
	class MeshFactory;
	class TextureFactory;

	class PollingStation
	{
		friend class Engine;
	public:
		inline GraphicsEngine* GetGraphicsEngine() noexcept { return myGraphicsEnginePtr; }
		inline ShaderFactory* GetShaderFactory() noexcept { return myShaderFactoryPtr; }
		inline Renderer* GetRenderer() noexcept { return myRendererPtr; }
		inline MeshFactory* GetMeshFactory() noexcept { return myMeshFactoryPtr; }
		inline TextureFactory* GetTextureFactory() noexcept { return myTextureFactory; }
	private:
		ShaderFactory* myShaderFactoryPtr;
		GraphicsEngine* myGraphicsEnginePtr;
		Renderer* myRendererPtr;
		MeshFactory* myMeshFactoryPtr;
		TextureFactory* myTextureFactory;
	};
}