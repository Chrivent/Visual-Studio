#pragma once
struct Vertex
// 앞으로 우리가 도형을 만들 때 쓸 정점의 정보는 이 구조체를 통해 관리함
{
	Float3 position; // 정점의 위치
					 // 우리가 실제로 다루는건 2D이지만
					 // 기본적으로는 3D 쪽의 기능을 이용해서 2D를 다루는 것이기 때문에
					 // 사용하는 함수 등의 구격에 맞게 x, y, z 3개 차원의 데이터를
					 // 전부 구성은 해둬야 함 -> 사용은 안 하더라도 z값은 일단 가지게 만듦

	Float4 colour; // 정점이 가지고 있는 색
				   // RGB값을 이용해서 색을 결정하나,
				   // 여기에 추가로 alpha값이라는 데이터를 같이 저장함

	Vertex()
		// C++에선 구조체는 사실상 public만 존재하는 클래스라 봐도 무방
		// 이렇게 생성자를 만드는 것도 문제 X
		// 아무 입력 없이 디폴트 선언했읋 때의 초기화값
	{
		position = Float3(0, 0, 0);
		colour = Float4(0, 0, 0, 1);
		// RGB값 외에 4번째 값인 알파값은 사용할 기회가 왔을 때 실행
	}
	Vertex(float x, float y, float r, float g, float b)
	{
		position = Float3(x, y, 0);
		// 2D에선 z축의 위치를 사용하지 않음
		colour = Float4(r, g, b, 1);
		// DX에서는 RGB값을 이용할 때
		// 0.0f ~ 1.0f까지의 값을 통해 백분율로서 색상을 표시함
	}
};

// 원래라면 여기서 끝이지만
// DX는 화면 좌표를 디폴트로는 -1.0~1.0까지로 이용하는 상대좌표계이므로
// 이를 변환해줄 함수가 필요함
// 기존에 만들었던 함수를 가져옴

static float ratio_pos_x(int pos_x)
// 입력한 절대좌표를 DX에서 사용할 수 있는 상대좌표로 변환하는 함수
// 지금은 이걸 쓰지만 나중엔 다른 기능으로 대체 예정
{
	float ratio = ((float)pos_x - WIN_CENTER_X) / (float)WIN_CENTER_X;

	return ratio;
}

static float ratio_pos_y(int pos_y)
{
	float ratio = -((float)pos_y - WIN_CENTER_Y) / (float)WIN_CENTER_Y;

	return ratio;
}
