#include "precompile-header/coreIncludes.h"
#include "ConstantBuffer.h"
#include "graphics/GraphicsEngine.h"
#include "logging/Logger.h"

std::unordered_map<size_t, GBuffer> drach::ConstantBuffer::myBuffers;

void drach::ConstantBuffer::Bind(GraphicsEngine& anEngine, void* someData, size_t someDataSize, const size_t aSlot, const size_t aBindSetting)
{
	GDContext& context = anEngine.GetContext();
	D3D11_MAPPED_SUBRESOURCE resource;
	context->Map(myBuffers[someDataSize].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	resource.pData = someData;
	context->Unmap(myBuffers[someDataSize].Get(), 0);

	if (aBindSetting == 0 || aBindSetting == static_cast<size_t>(BindType::Pixel))
		context->PSSetConstantBuffers(aSlot, 1, &myBuffers[someDataSize]);
	if (aBindSetting == 0 || aBindSetting == static_cast<size_t>(BindType::Vertex))
		context->VSSetConstantBuffers(aSlot, 1, &myBuffers[someDataSize]);
}

GBuffer drach::ConstantBuffer::InitializeGBuffer(GraphicsEngine& anEngine, size_t someDataSize)
{
	GBuffer buffer;
	GDevice& device = anEngine.GetDevice();

	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = someDataSize;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data = {};

	HRESULT result = device->CreateBuffer(&desc, nullptr, &buffer);

	if (FAILED(result))
	{
		LOG_ERROR("Failed to create constant buffer!");
		return buffer;
	}

	myBuffers[someDataSize] = buffer;

	return buffer;
}
