#pragma once
#include <wrl.h>
#include <d3d10.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dcommon.h>
#include <d3d11shader.h>
#include <string_view>

using Microsoft::WRL::ComPtr;

typedef ComPtr<IDXGISwapChain> SwapChain;
typedef ComPtr<ID3D11RenderTargetView> RenderTarget;
typedef ComPtr<ID3D11DepthStencilView> DepthStencil;
typedef ComPtr<ID3D11ShaderResourceView> RenderResource;
typedef ComPtr<ID3D11Device> GDevice;
typedef ComPtr<ID3D11DeviceContext> GDContext;
typedef ComPtr<ID3D11Buffer> GBuffer;
typedef ComPtr<ID3D11VertexShader> VertexShader;
typedef ComPtr<ID3D11PixelShader> PixelShader;
typedef ComPtr<ID3D11InputLayout> InputLayout;
typedef ComPtr<ID3D11Texture2D> GTexture;
typedef ComPtr<ID3DBlob> Blob;
typedef ComPtr<ID3D11ShaderReflection> ShaderInfo;
typedef ComPtr<ID3D11SamplerState> SamplerState;