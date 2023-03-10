#include "precompile-header/coreIncludes.h"
#include "ConstantBuffer.h"
#include "graphics/GraphicsEngine.h"
#include "logging/Logger.h"




drach::ConstantBuffer::ConstantBuffer() = default;

drach::ConstantBuffer::ConstantBuffer(GraphicsEngine& anEngine)
	:myEngine(&anEngine)
{
}

void drach::ConstantBuffer::Bind(const size_t aTypeID, ConstantBuffer& anInstance, void* someData, size_t someDataSize, const size_t aSlot, const size_t aBindSetting)
{
	if (!anInstance.myEngine) return;
	if (anInstance.myBuffers[aTypeID].Get() == nullptr) return;
	ID3D11DeviceContext* context = anInstance.myEngine->GetContext();
	D3D11_MAPPED_SUBRESOURCE resource;
	context->Map(anInstance.myBuffers[aTypeID].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, someData, someDataSize);
	context->Unmap(anInstance.myBuffers[aTypeID].Get(), 0);

	if (aBindSetting == 0 || aBindSetting == static_cast<size_t>(BindType::Pixel))
		context->PSSetConstantBuffers(aSlot, 1, anInstance.myBuffers[aTypeID].GetAddressOf());
	if (aBindSetting == 0 || aBindSetting == static_cast<size_t>(BindType::Vertex))
		context->VSSetConstantBuffers(aSlot, 1, anInstance.myBuffers[aTypeID].GetAddressOf());
}

GBuffer drach::ConstantBuffer::Initialize(ConstantBuffer& anInstance, size_t someDataSize, size_t aTypeID)
{
	if (!anInstance.myEngine) return nullptr;
	GBuffer buffer = nullptr;
	ID3D11Device* device = anInstance.myEngine->GetDevice();

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

	anInstance.myBuffers[aTypeID] = buffer;
	LOG("Created a constant buffer!");

	return buffer;
}
