#include "framework.h"

Device* Device::instance = nullptr;
// 클래스에서 static으로 선언한 멤버 변수는
// 이렇게 파일 쪽에서 초기화를 해줘야 에러가 발생하지 않음

UINT width = WIN_WIDTH;
UINT height = WIN_HEIGHT;
// 창의 크기를 변수로써 사용해야 하는 상황이 있다보니
// 여기다가 전역 변수로서 이용

Device::Device()
{
	CreateDeviceAndSwapChain();
	CreateBackBuffer();
	SetViewPoint();
    // 3가지 초기화 함수를 생성자에서 실행
}

Device::~Device()
{
	device->Release();
	device_context->Release();

	swap_chain->Release();
	render_target_view->Release();
    // 생성자에서 동적 할당을 했던 클래스들은 여기서 이렇게 할당 해제
}

void Device::CreateDeviceAndSwapChain()
// 더블버퍼링 관련 설정을 초기화하는 함수
{
    DXGI_SWAP_CHAIN_DESC sd = {};

    sd.BufferCount = 1; 

    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    // 이 hWnd만큼은 외부에서 받아와서 사용해야 함
    // 그 때문에 이를 extern 전역 변수로 선언하고
    // 메인 파일에서 이를 초기화하는 것

    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true;

    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &sd,
        &swap_chain,
        &device,
        nullptr,
        &device_context
    );

    // 기존의 더블버퍼링을 설정하는 부분을 그대로 가져옴
}

void Device::CreateBackBuffer()
// 백버퍼를 초기화하고 디바이스에 등록하는 함수
{
    ID3D11Texture2D* backBuffer = nullptr;

    swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &render_target_view);
    backBuffer->Release();

    device_context->OMSetRenderTargets(1, &render_target_view, nullptr);

    // 지난 프로젝트에서 백버퍼를 설정하고 디바이스에 이를 등록하는 부분을 가져옴
}

void Device::SetViewPoint()
// 뷰포트: 우리가 3D 공간에서는 뭔가를 볼 때 설정해야 하는 내용들을 설정하는 부분
//         ...2D에서는 기본적으로 이걸 건드릴 일이 많지 않기 때문에 설명하지 않음
{
    D3D11_VIEWPORT viewPort;
    viewPort.Width = width; // 우리가 설정한 창의 크기 전체를 화면에 표시하겠다
    viewPort.Height = height; // 마찬가지
    viewPort.MinDepth = 0.0f; // 깊이를 따지는 내용
    viewPort.MaxDepth = 1.0f; // 이에 대해서는 추후 3D를 배울 떄 다루게 될 것
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    device_context->RSSetViewports(1, &viewPort);

    // 기존에 뷰포트를 세팅할 때 사용했던 코드를 그대로 가져와 사용

}

void Device::Clear()
// 화면을 초기화하는 함수
{
    float clear_color[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    device_context->ClearRenderTargetView(render_target_view, clear_color);
    // 배경색을 지정한 후, 그 값을 이용해 화면 전체를 채우는 식으로 화면 초기화
}

void Device::Present()
// 더블버퍼링을 실행하는 함수
{
    swap_chain->Present(0, 0);
}
