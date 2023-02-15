#pragma once
#include <unordered_map>
#include "graphics/DirectX11/DXTypes.h"
namespace drach
{
	class GraphicsEngine;

	enum class BindType
	{
		Both, Vertex, Pixel
	};

	class ConstantBuffer
	{

	public:
		template<typename Type, BindType aBindType>
		static void Bind(GraphicsEngine& anEngine, const Type& aType, const size_t aSlot);

		template<typename Type>
		static void Initialize(GraphicsEngine& anEngine);

	private:
		static void Bind(GraphicsEngine& anEngine, void* someData, size_t someDataSize, const size_t aSlot, const size_t aBindSetting = 0);

		static GBuffer InitializeGBuffer(GraphicsEngine& anEngine, size_t someDataSize);
	private:
		static std::unordered_map<size_t, GBuffer> myBuffers;
	};
	template<typename Type, BindType aBindType>
	inline void ConstantBuffer::Bind(GraphicsEngine& anEngine, const Type& aType, const size_t aSlot)
	{
		ConstantBuffer::Bind(anEngine, (void*)&aType, sizeof(Type), aSlot, static_cast<size_t>(aBindType));
	}


	template<typename Type>
	inline void ConstantBuffer::Initialize(GraphicsEngine& anEngine)
	{
		static GBuffer buffer = InitializeGBuffer(anEngine, sizeof(Type));
	}
}