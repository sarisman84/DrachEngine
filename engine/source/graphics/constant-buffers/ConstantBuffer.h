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
		ConstantBuffer();
		ConstantBuffer(GraphicsEngine& anEngine);
	public:
		template<typename Type, BindType aBindType>
		static void Bind(ConstantBuffer& anInstance, const Type& aType, const size_t aSlot);

		template<typename Type>
		static void Initialize(ConstantBuffer& anInstance);

	private:
		static void Bind(ConstantBuffer& anInstance, void* someData, size_t someDataSize, const size_t aSlot, const size_t aBindSetting = 0);

		static GBuffer Initialize(ConstantBuffer& anInstance, size_t someDataSize);
	private:
		std::unordered_map<size_t, GBuffer> myBuffers;
		GraphicsEngine* myEngine;
	};
	template<typename Type, BindType aBindType>
	inline void ConstantBuffer::Bind(ConstantBuffer& anInstance, const Type& aType, const size_t aSlot)
	{
		ConstantBuffer::Bind(anInstance, (void*)&aType, sizeof(Type), aSlot, static_cast<size_t>(aBindType));
	}


	template<typename Type>
	inline void ConstantBuffer::Initialize(ConstantBuffer& anInstance)
	{
		ConstantBuffer::Initialize(anInstance, sizeof(Type));
	}
}