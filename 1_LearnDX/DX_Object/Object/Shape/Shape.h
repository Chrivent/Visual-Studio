#pragma once
/*
	게임을 구성하는 오브젝트는 "게임적 구현"을 담당하는 파트와
	"그래픽 구성"을 담당하는 파트로 나뉜다고 할 수 있으며
	
	이는 그 하나의 오브젝트를 구성할 때 각각을 담당하는 게부 클래스로서 나눠
	해당 오브젝트를 관리하는 것으로 구현하게 됨

	지금부터 만들 Shape라는 클래스는
	그 "그래픽"을 담당한다는 것이 무슨 의미인지를 체험하기 위해서 사용하는 클래스

	단, 이 클래스는 본격적인 3D 그래픽스 이론을 적용하지 않고 만드는 임시 클래스
	때문에 단기간 동안만 사용하고 그 뒤에는 재구성할 예정
*/

class Shape
{
protected:
	vector<Vertex> vertices = {};
	// Vertex를 저장하는 vector를 만들어두어,
	// 이 도형이 출력되는 데 사용할 정점을 저장할 자료구조를 구성

	float pos_x, pos_y; //@
	// 도형의 위치를 기록해둘 변수
	// (이번에만 사용하고, 본격적으로 3D 그래픽 이론을 적용할 땐 삭제할 대상)
	// 앞으로 이런 변수는 뒤에 각주로 @ 표시

	ID3D11Buffer* VB; //@
	// 도형 각각이 그래픽 출력에 필요한 데이터를 알아서 저장하도록,
	// 각 객체가 멤버로 버퍼를 보유하도록 만든다

public:
	Shape(float x, float y);
	~Shape();

	ID3D11Buffer** const GetBuffer() { return &VB; }
	int GetVertexSize() { return vertices.size(); }
};