// CK_DX_02_01_BasicRenderTriangle.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "CK_DX_02_01_BasicRenderTriangle.h"

// WinMain 함수 
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    // 디버그 빌드 할때 CRT를 이용한 런타임 메모리릭 찾기를 수행
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    CKDX_BasicRenderTriangleApp theApp(hInstance);

    /*char* cp;
    cp = (char*)malloc(16);*/

    if (!theApp.Init())
        return 0;

    return theApp.Run();
}

//========================================================================
// Description CKDX_BasicRenderTriangleApp 
//========================================================================
CKDX_BasicRenderTriangleApp::CKDX_BasicRenderTriangleApp(HINSTANCE hInstance)
	: D3DApp(hInstance), mTriVB(0),mFX(0), mTech(0),
	mfxWorldViewProj(0), mInputLayout(0),
	mTheta(1.5f * MathHelper::Pi), mPhi(0.25f * MathHelper::Pi), mRadius(5.0f)
{
	mMainWndCaption = L"CK_DX_02_01_BasicRenderTriangle Demo";

	mLastMousePos.x = 0;
	mLastMousePos.y = 0;

	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&mWorld, I);
	XMStoreFloat4x4(&mView, I);
	XMStoreFloat4x4(&mProj, I);
}

CKDX_BasicRenderTriangleApp::~CKDX_BasicRenderTriangleApp()
{
	ReleaseCOM(mTriVB);	
	ReleaseCOM(mFX);
	ReleaseCOM(mInputLayout);
}

bool CKDX_BasicRenderTriangleApp::Init()
{
	if (!D3DApp::Init())
		return false;

	BuildGeometryBuffers();
	BuildFX();
	BuildVertexLayout();
	return true;
}

void CKDX_BasicRenderTriangleApp::OnResize()
{
	D3DApp::OnResize();

	// The window resized, so update the aspect ratio and recompute the projection matrix.
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
	XMStoreFloat4x4(&mProj, P);
}

void CKDX_BasicRenderTriangleApp::UpdateScene(float dt)
{
	// Build the view matrix.	
	XMVECTOR pos = XMVectorSet(0.0f, 0.0f, -5.0f, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX V = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&mView, V);
}

void CKDX_BasicRenderTriangleApp::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::LightSteelBlue));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	md3dImmediateContext->IASetInputLayout(mInputLayout);
	md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	md3dImmediateContext->IASetVertexBuffers(0, 1, &mTriVB, &stride, &offset);
	
	// Set constants
	XMMATRIX world = XMLoadFloat4x4(&mWorld);
	XMMATRIX view = XMLoadFloat4x4(&mView);
	XMMATRIX proj = XMLoadFloat4x4(&mProj);
	XMMATRIX worldViewProj = world * view * proj;

	mfxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	D3DX11_TECHNIQUE_DESC techDesc;
	mTech->GetDesc(&techDesc);

	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		mTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);

		// 3 vertex for the triangle
		md3dImmediateContext->Draw(3, 1);
	}

	HR(mSwapChain->Present(0, 0));
}

void CKDX_BasicRenderTriangleApp::BuildGeometryBuffers()
{
	// Create vertex buffer
	Vertex vertices[] =
	{
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Red)   },
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Red)   },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Red)   },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Red)   },
	};

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * 4;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;
	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mTriVB));	
}

void CKDX_BasicRenderTriangleApp::BuildFX()
{
	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3DCOMPILE_DEBUG;
	shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* compiledErrorMsg = 0;

	HRESULT hr = D3DX11CompileEffectFromFile(L"FX/tri.fx",
		NULL,
		NULL,
		shaderFlags,
		0,
		md3dDevice,
		&mFX,
		&compiledErrorMsg);

	// compiledErrorMsg can store errors or warnings.
	if (compiledErrorMsg != 0)
	{
		MessageBoxA(0, (char*)compiledErrorMsg->GetBufferPointer(), 0, 0);
		ReleaseCOM(compiledErrorMsg);
	}

	// Even if there are no compiledErrorMsg, check to make sure there were no other errors.
	if (FAILED(hr))
	{
		MessageBoxA(0, "Error D3DX11CompileEffectFromFile", 0, 0);
	}

	mTech = mFX->GetTechniqueByName("ColorTech");
	mfxWorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void CKDX_BasicRenderTriangleApp::BuildVertexLayout()
{
	// Create the vertex input layout.
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// Create the input layout
	D3DX11_PASS_DESC passDesc;	
	mTech->GetPassByIndex(0)->GetDesc(&passDesc);

	// CreateInputLayout를 통해서 정점 버퍼를 어떻게 해석할지 GPU에게 알려준다.
	HR(md3dDevice->CreateInputLayout(vertexDesc, 2, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &mInputLayout));
}

