#pragma once
#include "graphics/DirectX11/DXTypes.h"
#include "util/other/Object.h"
#include <memory>
#include <wtypes.h>
#include <cstdint>
#include <unordered_map>
namespace drach
{
	namespace dx11
	{
		struct PixelCoords
		{
			uint32_t x;
			uint32_t y;
		};
		enum class BufferType
		{
			Pixel, Vertex
		};


		HRESULT BindResource(GraphicsDeviceContext& aContext, RenderResource& aResource, const size_t aSlot, const size_t anAmount = 1);
		HRESULT BindConstantBuffer(GraphicsDeviceContext& aContext, const BufferType aBufferTYype, GBuffer& aBuffer, const size_t aSlot, const size_t anAmount = 1);
		void SetViewport(GraphicsDeviceContext& aContext, const PixelCoords& aSize, const PixelCoords& aStart, const uint32_t aMinDepth, const uint32_t aMaxDepth);
		void ClearDepthStencil(GraphicsDeviceContext& aContext, DepthStencil& aStencil);
		void ClearRenderTarget(GraphicsDeviceContext& aContext, RenderTarget& aTarget);


		class RenderBuilder
		{
		public:
			RenderBuilder(GraphicsDevice& aDevice);

			static inline void Init(GraphicsDevice& aDevice);
			static inline RenderBuilder& API() noexcept { return *ourInstance; }
			static inline void Release();

			RenderBuilder& InitRenderTarget(RenderTarget& aRenderTargetToInit, D3D11_TEXTURE2D_DESC& aDesc, HRESULT* someResult = nullptr);
			RenderBuilder& InitRenderResource(RenderResource& aRenderResourceToInit, D3D11_TEXTURE2D_DESC* aDesc, HRESULT* someResult = nullptr);
			RenderBuilder& InitDepthStencil(DepthStencil& aDepthStencilToInit, D3D11_DEPTH_STENCIL_VIEW_DESC& aDesc, HRESULT* someResult = nullptr);

		private:
			template<typename Type>
			Type& Data(const std::string& anID)
			{
				if (myBlackboard.count(anID) <= 0)
					myBlackboard[anID] = std::make_shared<Object<Type>>();

				return myBlackboard[anID]->As<Object<Type>>().myData;
			}

		private:

			GraphicsDevice& myDevice;
			std::unordered_map<std::string, std::shared_ptr<BaseObject>> myBlackboard;
		private:
			static RenderBuilder* ourInstance;
		};

	}
}