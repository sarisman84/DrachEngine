#include "precompile-header/coreIncludes.h"
#include "Mesh.h"
#include "graphics/GraphicsEngine.h"

void drach::Mesh::Bind(GraphicsEngine& anEngine)
{
	ID3D11DeviceContext* context = anEngine.GetContext();

	uint32_t strife = sizeof(Vertex);
	uint32_t offset = 0;

	context->IASetVertexBuffers(0, 1, myVertexBuffer.GetAddressOf(), &strife, &offset);
	context->IASetIndexBuffer(myIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}
