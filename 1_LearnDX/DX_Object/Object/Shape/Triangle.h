#pragma once

//삼각형을 담당하는 Shape 자식 클래스
class Triangle : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;
	// DeviceContext에 어떤 도형을 이번에 출력할 것인지 알리는데 사용할 열거형
	// 열거형이란 특성상 + 이 열거형이 가지고 있는 각각의 이름들이 매우 길어서
	// 변수로서 만들어 이름을 붙이는 것으로 
	// 아프올 이 인스턴스가 담당하는 도형을 출력할 때 일일이 입력할 필요 없게
	// 쉽게 이용할 수 있도록 하는 것

public:
	Triangle(float x = 0, float y = 0, D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
};