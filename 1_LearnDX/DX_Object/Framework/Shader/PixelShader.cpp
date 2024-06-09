#include "framework.h"

PixelShader::PixelShader(LPCWSTR file_loc, DWORD flags)
{
    // VertexShader 측과 하는 것은 똑같음:
    // 파일명을 받아서 그걸 이용해 셰이더를 컴파일하고
    // 그걸 토대로 만들어진 세이더 인스턴스를 PS에 저장

    // 다만 픽셀 셰이더는 정점 셰이더에 
    // 셰이더를 만드는 데 비해서 필요한 데이터가 더 적어
    // 일부 내용만 실행하게 됨

    ID3DBlob* pixelBlob;
    D3DCompileFromFile(L"Shader/VertexShader.hlsl", nullptr, nullptr, "PS",
        "ps_5_0", flags, 0, &pixelBlob, nullptr);

    Device::Get()->GetDevice()->CreatePixelShader(pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(), nullptr, &PS);
    pixelBlob->Release();
}

PixelShader::~PixelShader()
{
	Release();
}

void PixelShader::Release()
{
	PS->Release();
}
