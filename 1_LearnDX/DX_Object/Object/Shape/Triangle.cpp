#include "framework.h"
#include "Triangle.h"

Triangle::Triangle(float x, float y, D3D11_PRIMITIVE_TOPOLOGY t)
	: Shape(x, y), type(t)
{
	vertices.emplace_back(x, y + 0.2f, 1.0f, 0.0f, 0.0f);
	vertices.emplace_back(x + 0.15f, y - 0.1f, 0.0f, 1.0f, 0.0f);
	vertices.emplace_back(x - 0.15f, y - 0.1f, 0.0f, 0.0f, 1.0f);
	// Shape가 가지고 있는 정점을 보관하는 벡터에
	// 입력받은 좌표를 이용해서 정점들을 정의하여 저장하는 작업을 진행
	vertices.emplace_back(x, y - 0.4f, 1.0f, 0.0f, 0.0f);
	vertices.emplace_back(x - 0.15f, y - 0.1f, 0.0f, 1.0f, 0.0f);
	vertices.emplace_back(x + 0.15f, y - 0.1f, 0.0f, 0.0f, 1.0f);
	// 이런 식으로, 삼각형을 여럿 만드는 것으로 
	// 정확히는 그림을 그리는데 사용될 정점들을 더 입력하는 것으로
	// 삼각형만이 아닌 다른 도형을 만드는 것이 가능하다

	/*
				*과제*
		위에서 선보인 것처럼,
		그리고 이번 시간에 Triangle이라는 클래스를 만들어서
		출력해보는 과정을 거친 것처럼

		저번에 과제로 제시되었던 "원하는 도형을 새로이 그려본다"라는 과제를
		똑같지만, 이번에는 해당 도형을 지금의 이 삼각형처럼 전담하는 클래스를 만들어서
		Scene에서는 그 클래스의 객체를 만들어 출력하기만 하는 식으로 프로그램을 구성해볼 것

		-> 이번에 우리가 삼각형을 그렸던 것처럼,

		별 같은 것을 만들고자 할 경우
		Star같은 클래스를 만들어서 그 클래스가 별을 출력하도록 만들고
		그렇게 만들어진 클래스를 ObjectTrialScene의 멤버 변수로서 만들어
		화면에 출력되도록 만들어보기
	*/

	// 아래의 내용은 기존의 TutorialScene의 생성자 최하단에 있던 내용을 가져온 것
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * vertices.size(); 
	// 위에서 구성한 정점들의 총 개수
	// 이 부분은 배열을 썼던 기존과는 다르게
	// 사용한 데이터의 크기 * 그 데이터의 개수로 직접 용량을 계산

	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices.data();
	// vertices 라는 것이 다른 것을 칭하게 바뀌었으니
	// 그에 맞게 이 부분도 수정

	Device::Get()->GetDevice()
		->CreateBuffer(&bd, &initData, &VB);
	// 버퍼를 담당하는 변수의 이름도
	// 이 클래스에 맞게 재조정

	// 이렇게 하여, 정점 셰이더에 우리가 구성했던 정점 데이터들을
	// 전달할 준비를 버퍼에 넣어 끝마침

	// 여기까지 내용은 기존에는 우리가 만들었던 Scene에서 전부 담당헀던 내용으로,
	// 이제는 그 중 각각의 오브젝트(지금은 삼각형을 담당하는 오브젝트)에서
	// 관련 내용을 전부 처리하도록 하여 Scene 쪽에서는 신경쓸 여지가 적게 만든다
}

// 소멸자가 없는데,
// 이는 여기서 우리가 emplace_back을 이용해 vector에 데이터를 저장한 것 외엔
// 특별히 동적 할당을 한게 없음
// 그래서 굳이 소멸자를 통해서 이를 전부 관리해야 할 필요성이 적은 것