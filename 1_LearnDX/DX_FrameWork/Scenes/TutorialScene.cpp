#include "framework.h"
ID3D11Buffer* vertex_buffer;

TutorialScene::TutorialScene()
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	// 셰이더 생성에 필요한 플래그를 미리 설정

	VS = new VertexShader(L"Shader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"Shader/VertexShader.hlsl", flags);
	// 정점 셰이더와 픽셀 셰이더를 셰이더 주소가 있는 파일에 생성

	// 이제 도형을 그리는 데 사용할 정점 생성
	// DX는 기본적으로 선, 삼각형만 출력 가능
	// 그 삼각형을 출력하기 위해선 해당 삼각형을 구성하는 정점들이 필요함
	
	// 그래서 그 정점 = 꼭짓점을 아래와 같이 미리 선언해두는 것
	Vertex vertices[] =
	{
		Vertex(-0.1f, +0.1f, 0.8f, 0.8f, 0.17f),
		Vertex(-0.8f, +0.1f, 0.8f, 0.8f, 0.17f),
		Vertex(-0.8f, +0.8f, 0.8f, 0.8f, 0.17f),

		Vertex(+0.1f, +0.1f, 1.0f, 1.0f, 1.0f),
		Vertex(+0.1f, +0.8f, 0.0f, 0.5f, 1.0f),
		Vertex(+0.8f, +0.8f, 1.0f, 0.5f, 1.0f),
		// DX의 기본값으로는
		// 화면 전체의 좌표계를
		// 왼쪽 아래를 -1, -1, 오른쪽 위를 +1, +1로 취급하여
		// 화면 중앙에서 전체 화면 비율로 얼마나 떨어져있는가로서
		// 좌표를 표기하는 상대좌표 방식

		// 정점을 그릴 때 주의해야할 점:
		// 지금 우리가 2D 그래픽을 그리고 있기는 하나
		// 기본적으로 3D 그래픽을 출력한느 원리를 이용해서 화면을 구성 중
		// 이에 따라, 화면을 구성하기 위해서 우리는 필연적으로 
		// 우리가 그리는 폴리곤의 "앞뒷면" 개념을 이해해야만 함

		// 앞뒷면 개념을 통해서 "어느 부분이 화면에 보이고
		// 어느 부분이 화면에 보이지 않도록 제어할 것인지"
		// 이를 분류할 기준이 필요함

		// 그래서 폴리곤의 정점들이 "시계방향"을 이루는 방향을
		// 폴리곤의 "앞면"이라 정의하고,
		// 반대로 시계 반대방향을 이루는 측면을
		// 폴리곤의 "뒷면"이라 정의해서
		// 화면상에는 폴리곤의 앞면만을 출력하도록 DX가 구성됨

		// 그래서 지금 이렇게 그림을 그리기 위해 구성한 꼭짓점들이
		// 시계방향을 그리고 있지 않다면 출력되지 않음
		// 이에 대한 자세한 개념은 3D를 다루게 되는 심화반 쪽에서 배우시게 될 것
		// 지금은 "꼭짓점은 반드시 시계방향을 그려야만 한다"라고 기억하면 ok
	};

	// 그렇게 정점을 선언했다 하더라도,
	// 위의 형식대로는 다음 단계에서 처리를 못 하기 때문에
	// 다음 단계에서 처리가 가능한 형태,
	// 즉 Id3D11buffer의 형태로 데이터를 정리할 필요가 있음
	// 그래서 해당 형식대로 버퍼를 만드는 것
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(vertices); // 위에서 구성한 정점들의 총 개수
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;

	Device::Get()->GetDevice()
		->CreateBuffer(&bd, &initData, &vertex_buffer);
}

TutorialScene::~TutorialScene()
{
	VS->Release();
	PS->Release();
}

void TutorialScene::Update()
// 메인 프로그램의 매 루프마다 씬의 현재 상황을 업데이트하는 함수
// 시간 경과 등에 따라 씬의 내용이 변해야 한다면 이 함수를 통해 변동사항을 관리

// ...하지만 오늘은 이 함수를 사용할 일이 없으니 빈 함수로 놔둠
{


}

void TutorialScene::Render()
// 실제 출력을 담당하는 부분
// 이 씬이 사용중일 떄, 메인 루프가 돌아갈 때마다 이 함수를 통해 화면에 출력
{
	Device::Get()->Clear();
	// 화면을 초기화시키는 함수를 Device에서 불러 사용

	UINT stride = sizeof(Vertex);
	UINT offset = 0;


	Device::Get()->GetDeviceContext()->VSSetShader(VS->GetVertexShader(), nullptr, 0);
	Device::Get()->GetDeviceContext()->PSSetShader(PS->GetPixelShader(), nullptr, 0);
	// 디바이스에 정점 셰이더와 픽셀 셰이더를 설정

	Device::Get()->GetDeviceContext()->IASetInputLayout(VS->GetInputLayout());
	// VS 내부의 input_layout을 가져와 device_context에 세팅

	// 여기까지는 그리기 전에 Scene을 그릴 환경을 세팅하는 부분
	// 여기부터는 본격적으로 도형을 그리는 부분

	Device::Get()->GetDeviceContext()->IASetVertexBuffers
	(0, 1, &vertex_buffer, &stride, &offset);
	// 삼각형이 보유하고 있는 정점이 저장된 버퍼를 디바이스에 세팅
	Device::Get()->GetDeviceContext()->IASetPrimitiveTopology
	(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	// 도형을 그릴 방식을 디바이스에 세팅
	// -> 앞으로 그릴 도형이 어떤 도형인지를 이 함수를 통해 알린다.

	// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
	// 삼각형을 그리라는 뜻이나,
	// 그 삼각형을 그릴때 무조건 꼭짓점을 3개 단위로 끊어서 이용할 것
	// 입력된 정점들을 한 번에 삼각형을 출력할 때 앞에서부터 3개씩,
	// 중복되는 정점 없이 이용할 것

	// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
	// 마찬가지로 삼각형을 그리라는 뜻이지만,
	// 마지막에 사용했던 꼭짓점 중 뒤쪽의 2개를 재활용해서 
	// 삼각형을 그리도록 하는 모드
	// ex| 1,2,3,4 라는 4개의 정점을 이용해 그렸을 때
	//	   TRIANGLELIST 1,2,3 3개만 이용해 그리고 끝나지만
	//     TRIANGLESTRIP은 1,2,3으로 그린 뒤에 4,3,2를 이용해
	//	   한번 더 그리는 식

	// 위와 같은 식으로, 삼각형 대신 선을 그리는
	// LINELEIST, LINESTRTIP도 있음

	Device::Get()->GetDeviceContext()->Draw(6, 0);
	// 세팅을 다 끝냈으면 삼각형이 보유하고 있는 정점의 개수만큼 도형을 그리라고 요청
	// 3: 삼각형을 그리는데 사용할 정점의 개수
	// 0: 입력된 전체 정점들 중 몇번째 정점부터 사용할 것인지
	// -> 전체 정점들 중 0번 인덱스부터 총 3개의 정점을 이용해 그림을 그려라
}

/*
				과제
	한번 오늘 설명을 들은 걸 이용해서 
	삼각형, 사각형 외의 다른 도형을 한 번 그려볼 것

*/