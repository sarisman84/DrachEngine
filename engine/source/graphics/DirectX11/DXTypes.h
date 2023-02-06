#pragma once
#include <wrl.h>
#include <d3dcompiler.h>
#include <d3dcommon.h>
using Microsoft::WRL::ComPtr;

struct IDXGISwapChain;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11ShaderResourceView;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Buffer;
struct ID3D11DepthStencilState;
struct ID3D11RasterizerState;
struct ID3D11InputLayout;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11SamplerState;
struct ID3D11Texture2D;

enum DXGI_FORMAT;
enum D3D11_INPUT_CLASSIFICATION;

struct D3D11_TEXTURE2D_DESC;
struct D3D11_SHADER_RESOURCE_VIEW_DESC;
struct D3D11_DEPTH_STENCIL_VIEW_DESC;
struct D3D11_INPUT_ELEMENT_DESC;

typedef ComPtr<IDXGISwapChain> SwapChain;
typedef ComPtr<ID3D11RenderTargetView> RenderTarget;
typedef ComPtr<ID3D11DepthStencilView> DepthStencil;
typedef ComPtr<ID3D11ShaderResourceView> RenderResource;
typedef ComPtr<ID3D11Device> GraphicsDevice;
typedef ComPtr<ID3D11DeviceContext> GraphicsDeviceContext;
typedef ComPtr<ID3D11Buffer> GBuffer;
typedef ComPtr<ID3D11VertexShader> VertexShader;
typedef ComPtr<ID3D11PixelShader> PixelShader;
typedef ComPtr<ID3D11InputLayout> InputLayout;
typedef ComPtr<ID3D11Texture2D> GTexture;
typedef ComPtr<ID3DBlob> Blob;