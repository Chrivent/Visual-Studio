#include "framework.h"
#include "ObjectTrialScene.h"

ObjectTrialScene::ObjectTrialScene()
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	// 셰이더 생성에 필요한 플래그를 미리 설정

	VS = new VertexShader(L"Shader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"Shader/VertexShader.hlsl", flags);
	// 정점 셰이더와 픽셀 셰이더를 셰이더 주소가 있는 파일에 생성
	// 추가로, 원래대로라면 이 셰이더들은 셰이더를 이용해서 출력할 도형을 담당하는
	// 클래스 그 자체가 가지고 있어야 할 내용이나
	// 이번 시간까지는 그대로 이 쪽에서 이용함

	// 여기까진 기전의 씬에서 가져왔음

	t = new Triangle(0.5f, 0.5f);
	s = new Star(0.0f, 0.0f);
}

ObjectTrialScene::~ObjectTrialScene()
{
	delete t;
	delete s;
	delete VS;
	delete PS;
}

void ObjectTrialScene::Update()
{
}

void ObjectTrialScene::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;


	DVC->VSSetShader(VS->GetVertexShader(), nullptr, 0);
	DVC->PSSetShader(PS->GetPixelShader(), nullptr, 0);
	// 디바이스에 정점 셰이더와 픽셀 셰이더를 설정
	// 이렇게 DeviceContext를 가져올 일이 많은데
	// 이를 불러오는 코드로 그대로 쓰는건 너무 길어서 비효율적
	// 그래서 매크로를 선언하여 이를 최대한 짧게 줄인 것

	DVC->IASetInputLayout(VS->GetInputLayout());
	// 이 Scene이 사용하고 있는 VS의 내부에 있는 input_layout을 가져와
	// device_context에 세팅, 앞으로 어떤 자료가 셰이더에 넘어가는지
	// 장치에 알림

	DVC->IASetVertexBuffers(0, 1, t->GetBuffer(), &stride, &offset);
	DVC->IASetVertexBuffers(0, 1, s->GetBuffer(), &stride, &offset);
	// 삼각형을 담당한느 인스턴스인 t가 가지고 있는 정점이
	// 저장되어 있는 버퍼를 디바이스에 세팅

	DVC->IASetPrimitiveTopology(t->GetType());
	DVC->IASetPrimitiveTopology(s->GetType());
	// 삼각형이 보유하고 있는 도형을 그릴 방식을 디바이스에 세팅

	DVC->Draw(t->GetVertexSize(), 0);
	DVC->Draw(s->GetVertexSize(), 0);
	// 준비가 다 끝났으면 디바이스에 지금까지 입력했던 데이터들을 토대로 그려라
}
