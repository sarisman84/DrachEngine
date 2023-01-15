#pragma once
#include <wrl/client.h>
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

typedef ComPtr<IDXGISwapChain> SwapChain;
typedef ComPtr<ID3D11RenderTargetView> RenderTarget;
typedef ComPtr<ID3D11DepthStencilView> DepthStencil;
typedef ComPtr<ID3D11Device> GraphicsDevice;
typedef ComPtr<ID3D11DeviceContext> GraphicsDeviceContext;
typedef ComPtr<ID3D11Buffer> GraphicsBuffer;
typedef ComPtr<ID3D11VertexShader> VertexShader;
typedef ComPtr<ID3D11PixelShader> PixelShader;
typedef ComPtr<ID3D11InputLayout> InputLayout;