#pragma once

//�ﰢ���� ����ϴ� Shape �ڽ� Ŭ����
class Triangle : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;
	// DeviceContext�� � ������ �̹��� ����� ������ �˸��µ� ����� ������
	// �������̶� Ư���� + �� �������� ������ �ִ� ������ �̸����� �ſ� ��
	// �����μ� ����� �̸��� ���̴� ������ 
	// ������ �� �ν��Ͻ��� ����ϴ� ������ ����� �� ������ �Է��� �ʿ� ����
	// ���� �̿��� �� �ֵ��� �ϴ� ��

public:
	Triangle(float x = 0, float y = 0, D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
};