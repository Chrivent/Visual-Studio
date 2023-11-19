#pragma once

#include<Windows.h>
#include<d3d11.h>
#include<DirectXColors.h>
#include<d3dcompiler.h>

class Vector2
{
public:
	float x;
	float y;

	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}

	bool operator == (Vector2 vector2) const
	{
		if (x == vector2.x && y == vector2.y)
			return true;

		return false;
	}

	bool operator != (Vector2 vector2) const
	{
		return !(*this == vector2);
	}
};

class Vector3
{
public:
	float x;
	float y;
	float z;
	
	Vector3() : x(0), y(0), z(0) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	bool operator == (Vector3 vector3) const
	{
		if (x == vector3.x && y == vector3.y && z == vector3.z)
			return true;

		return false;
	}

	bool operator != (Vector3 vector3) const
	{
		return !(*this == vector3);
	}
};

class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion() : x(0), y(0), z(0), w(0) {}
	Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	bool operator == (Quaternion quaternion) const
	{
		if (x == quaternion.x && y == quaternion.y && z == quaternion.z)
			return true;

		return false;
	}

	bool operator != (Quaternion quaternion) const
	{
		return !(*this == quaternion);
	}
};

class Transform
{
public:
	Vector3 position;
	Quaternion rotation;
	Vector3 scale;

	Transform()
	{
		position = Vector3(0, 0, 0);
		rotation = Quaternion(0, 0, 0, 0);
		scale = Vector3(1, 1, 1);
	}
};

class GameObject
{
public:
	Transform transform;
};

inline void SetWindowPositionAndScale(HWND hWnd, int x, int y, int width, int height)
{
	SetWindowPos(hWnd, NULL, x, y, width, height, 0);
}

inline void SetClientPositionAndScale(HWND hWnd, int x, int y, int width, int height)
{
	SetWindowPos(hWnd, NULL, x, y, width + GetSystemMetrics(SM_CXFRAME) * 4, height + GetSystemMetrics(SM_CYFRAME) * 4 + GetSystemMetrics(SM_CYCAPTION), 0);
}

using namespace DirectX;

class D3DApp
{
public:
	~D3DApp()
	{
		if (g_pConstantBuffer) g_pConstantBuffer->Release();
		if (g_pVertexBuffer) g_pVertexBuffer->Release();
		if (g_pVertexLayout) g_pVertexLayout->Release();
		if (g_pVertexShader) g_pVertexShader->Release();
		if (g_pPixelShader) g_pPixelShader->Release();

		// Delte Direct3D
		if (g_RenderTargetView) g_RenderTargetView->Release();
		if (g_DepthStencilView) g_DepthStencilView->Release();
		if (g_SwapChain) g_SwapChain->Release();
		if (g_DepthStencilBuffer) g_DepthStencilBuffer->Release();
		if (g_d3dImmediateContext) g_d3dImmediateContext->ClearState();
		if (g_d3dDevice) g_d3dDevice->Release();
	}

private:
	ID3D11Device* g_d3dDevice = nullptr;
	ID3D11DeviceContext* g_d3dImmediateContext = nullptr;
	IDXGISwapChain* g_SwapChain = nullptr;
	ID3D11Texture2D* g_DepthStencilBuffer = nullptr;
	ID3D11DepthStencilView* g_DepthStencilView = nullptr;
	ID3D11RenderTargetView* g_RenderTargetView = nullptr;
	D3D11_VIEWPORT g_ScreenViewport;

	struct Vertex
	{
		XMFLOAT3 Pos;
	};

	struct CBufferObject
	{
		XMFLOAT4X4 World;
		XMFLOAT4X4 WorldViewProj;
	};

	// 상수버퍼용 값 추가
	XMMATRIX g_World;
	XMMATRIX g_View;
	XMMATRIX g_Proj;
	XMMATRIX g_WorldViewProj;

	ID3D11VertexShader* g_pVertexShader = nullptr;
	ID3D11PixelShader* g_pPixelShader = nullptr;
	ID3D11InputLayout* g_pVertexLayout = nullptr;
	ID3D11Buffer* g_pVertexBuffer = nullptr;

	// 상수버퍼
	ID3D11Buffer* g_pConstantBuffer = nullptr;

	float g_ObjScale = 1.0f;

public:
	void Init()
	{
		// UPDATE & RENDER
		g_d3dImmediateContext->ClearRenderTargetView(g_RenderTargetView,
			reinterpret_cast<const float*>(&DirectX::Colors::DimGray));
		g_d3dImmediateContext->ClearDepthStencilView(g_DepthStencilView, D3D11_CLEAR_DEPTH |
			D3D11_CLEAR_STENCIL, 1.0f, 0);
		g_SwapChain->Present(0, 0);
	}

	int Init(HWND hWnd, int width, int height)
	{
		// 1단계 : 디바이스와 컨텍스트 생성
		UINT createDeviceFlags = 0;
		D3D_DRIVER_TYPE d3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_FEATURE_LEVEL featureLevels[] =
		{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);
		D3D_FEATURE_LEVEL featureLevel;
		HRESULT hr = D3D11CreateDevice(
			0, // default adapter
			d3dDriverType, 0, // no software device
			createDeviceFlags,
			0, 0, // default feature level array
			D3D11_SDK_VERSION, &g_d3dDevice, &featureLevel, &g_d3dImmediateContext);
		if (FAILED(hr)) {
			MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
			return false;
		}
		if (featureLevel != D3D_FEATURE_LEVEL_11_0) {
			MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
			return false;
		}

		// 2단계 : H/W의 4X MSAA 품질 수준 지원 여부 확인
		UINT m4xMsaaQuality;
		g_d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
		if (m4xMsaaQuality <= 0)
		{
			MessageBox(0, L"Direct3D Feature 4x MSAA unsupported.", 0, 0);
			return false;
		}

		// 3단계 : SwapChain 생성을 위해 DXGI_SWAP_CHAIN_DESC 구조체 내용 구성
		DXGI_SWAP_CHAIN_DESC sd;
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.SampleDesc.Count = 4; // Use 4X MSAA
		sd.SampleDesc.Quality = m4xMsaaQuality - 1; // Use 4X MSAA
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = hWnd;
		sd.Windowed = true;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;

		// 4단계 : SwapChain의 생성
		IDXGIDevice* dxgiDevice = 0;
		if (FAILED(g_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice)))
			return false;
		IDXGIAdapter* dxgiAdapter = 0;
		if (FAILED(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter)))
			return false;
		IDXGIFactory* dxgiFactory = 0;
		if (FAILED(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory)))
			return false;
		if (FAILED(dxgiFactory->CreateSwapChain(g_d3dDevice, &sd, &g_SwapChain))) {
			return false;
		}
		dxgiDevice->Release();
		dxgiAdapter->Release();
		dxgiFactory->Release();

		// 5단계 : SwapChain의 BackBuffer에 대한 Render Target View 생성
		ID3D11Texture2D* backBuffer = nullptr;
		if (FAILED(g_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
			reinterpret_cast<void**>(&backBuffer)))) {
			MessageBox(0, L"Direct3D GetBuffer failed.", 0, 0);
			return false;
		}
		if (FAILED(g_d3dDevice->CreateRenderTargetView(backBuffer, 0, &g_RenderTargetView))) {
			MessageBox(0, L"Direct3D CreateRenderTargetView failed.", 0, 0);
			return false;
		};
		backBuffer->Release();

		// 6단계 : Depth Buffer, Stencil Buffer 생성 및 View 생성
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m4xMsaaQuality - 1;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;
		g_d3dDevice->CreateTexture2D(&depthStencilDesc, 0, &g_DepthStencilBuffer);
		g_d3dDevice->CreateDepthStencilView(g_DepthStencilBuffer, 0, &g_DepthStencilView);

		// 7단계 : RenderTargetView, Depth, Stencil View를 렌더링 파이프라인의 OutMerge단계의 결합 설정
		g_d3dImmediateContext->OMSetRenderTargets(1, &g_RenderTargetView, g_DepthStencilView);

		// 8단계 : Viewport에 대한 설정
		g_ScreenViewport.TopLeftX = 0;
		g_ScreenViewport.TopLeftY = 0;
		g_ScreenViewport.Width = static_cast<float>(width);
		g_ScreenViewport.Height = static_cast<float>(height);
		g_ScreenViewport.MinDepth = 0.0f;
		g_ScreenViewport.MaxDepth = 1.0f;
		g_d3dImmediateContext->RSSetViewports(1, &g_ScreenViewport);
	}

	HRESULT CompileShader(_In_ LPCWSTR srcFile, _In_ LPCSTR entryPoint, _In_ LPCSTR profile, _Outptr_ ID3DBlob** blob)
	{
		if (!srcFile || !entryPoint || !profile || !blob)
			return E_INVALIDARG;

		*blob = nullptr;

		UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
		flags |= D3DCOMPILE_DEBUG;
#endif

		ID3DBlob* shaderBlob = nullptr;
		ID3DBlob* errorBlob = nullptr;
		HRESULT hr = D3DCompileFromFile(srcFile, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, profile,
			flags, 0, &shaderBlob, &errorBlob);

		if (FAILED(hr))
		{
			if (errorBlob)
			{
				OutputDebugStringA((char*)errorBlob->GetBufferPointer());
				errorBlob->Release();
			}

			if (shaderBlob)
				shaderBlob->Release();

			return hr;
		}

		*blob = shaderBlob;
		return hr;
	}

	HRESULT InitShader()
	{
		HRESULT hr = S_OK;

		ID3DBlob* pVSBlob = nullptr;
		hr = CompileShader(L"ConstantBuffer.hlsl", "VS", "vs_4_0", &pVSBlob);

		if (FAILED(hr))
		{
			MessageBox(nullptr,
				L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return hr;
		}

		hr = g_d3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
		if (FAILED(hr))
		{
			pVSBlob->Release();
			return hr;
		}

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = ARRAYSIZE(layout);
 
		hr = g_d3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
			pVSBlob->GetBufferSize(), &g_pVertexLayout);
		pVSBlob->Release();

		if (FAILED(hr))
			return hr;

		g_d3dImmediateContext->IASetInputLayout(g_pVertexLayout);


		ID3DBlob* pPSBlob = nullptr;

		hr = CompileShader(L"ConstantBuffer.hlsl", "PS", "ps_4_0", &pPSBlob);

		if (FAILED(hr))
		{
			MessageBox(nullptr,
				L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return hr;
		}

		// 7) Pixel 셰이더 생성
		// Create the pixel shader
		hr = g_d3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &g_pPixelShader);
		pPSBlob->Release();

		if (FAILED(hr))
			return hr;

		return hr;
	}

	HRESULT BuildGeometry()
	{
		HRESULT hr = S_OK;
 
		Vertex vertices[] =
		{
			XMFLOAT3(0.0f, 0.5f, 0.5f),
			XMFLOAT3(0.5f, -0.5f, 0.5f),
			XMFLOAT3(-0.5f, -0.5f, 0.5f)
		};
		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(Vertex) * 3;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = {};
		InitData.pSysMem = vertices;
		hr = g_d3dDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);

		if (FAILED(hr))
			return hr;

		return hr;
	}

	HRESULT BuildConstants(int width, int height)
	{
		HRESULT hr = S_OK;

		float scaleValue = 1.0f;
		g_WorldViewProj = XMMatrixIdentity();

		// Init Value
		g_World = XMMatrixScaling(scaleValue, scaleValue, scaleValue);
		g_Proj = XMMatrixPerspectiveFovLH(0.25f * XM_PI, static_cast<float>(width) / height, 0.3f, 1000.0f);

		XMVECTOR pos = XMVectorSet(0.0f, 0.0f, -2.0f, 1.0f);
		XMVECTOR target = XMVectorZero();
		XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		g_View = XMMatrixLookAtLH(pos, target, up);

		g_WorldViewProj = g_World * g_View * g_Proj;

		// Supply the vertex shader constant data.
		CBufferObject VsConstData;
		XMStoreFloat4x4(&VsConstData.World, g_World);
		XMStoreFloat4x4(&VsConstData.WorldViewProj, g_WorldViewProj);

		// Fill in a buffer description.
		D3D11_BUFFER_DESC cbDesc;
		cbDesc.ByteWidth = sizeof(CBufferObject);
		cbDesc.Usage = D3D11_USAGE_DEFAULT;
		cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = 0;
		cbDesc.MiscFlags = 0;
		cbDesc.StructureByteStride = 0;

		// Fill in the subresource data.
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = &VsConstData;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;

		// Create the buffer.
		hr = g_d3dDevice->CreateBuffer(&cbDesc, &InitData, &g_pConstantBuffer);
		if (FAILED(hr))
			return hr;

		// Set the buffer.
		g_d3dImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
	}

	void Update()
	{
		CBufferObject VsConstData;
		g_ObjScale += 0.0001f;
		if (g_ObjScale > 1.5f) g_ObjScale = 1.0f;
		g_World = XMMatrixScaling(g_ObjScale, g_ObjScale, g_ObjScale);
		g_WorldViewProj = g_World * g_View * g_Proj;

		XMStoreFloat4x4(&VsConstData.World, g_World);
		XMStoreFloat4x4(&VsConstData.WorldViewProj, g_WorldViewProj);
		g_d3dImmediateContext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &VsConstData, 0, 0);
	}

	void Render()
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		g_d3dImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

		g_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		g_d3dImmediateContext->ClearRenderTargetView(g_RenderTargetView, Colors::DimGray);
		g_d3dImmediateContext->ClearDepthStencilView(g_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		g_d3dImmediateContext->VSSetShader(g_pVertexShader, nullptr, 0);
		g_d3dImmediateContext->PSSetShader(g_pPixelShader, nullptr, 0);
		g_d3dImmediateContext->Draw(3, 0);

		g_SwapChain->Present(0, 0);
	}
};
