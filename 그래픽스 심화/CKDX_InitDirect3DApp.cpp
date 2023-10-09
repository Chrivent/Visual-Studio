// 그래픽스 심화.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "CKDX_InitDirect3DApp.h"

CKDX_InitDirect3DApp::CKDX_InitDirect3DApp(HINSTANCE hInstance) : D3DApp(hInstance)
{

}

CKDX_InitDirect3DApp::~CKDX_InitDirect3DApp()
{

}

bool CKDX_InitDirect3DApp::Init()
{
    if (!D3DApp::Init())
        return false;

    return true;
}

void CKDX_InitDirect3DApp::OnResize()
{
    D3DApp::OnResize();
}

void CKDX_InitDirect3DApp::UpdateScene(float dt)
{

}

void CKDX_InitDirect3DApp::DrawScene()
{
    assert(md3dImmediateContext);
    assert(mSwapChain);

    md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Blue));
    md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    HR(mSwapChain->Present(0, 0));
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#endif
    CKDX_InitDirect3DApp theApp(hInstance);

    if (!theApp.Init())
        return 0;

    return theApp.Run();
}