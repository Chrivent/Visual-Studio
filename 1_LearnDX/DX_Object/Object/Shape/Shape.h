#pragma once
/*
	������ �����ϴ� ������Ʈ�� "������ ����"�� ����ϴ� ��Ʈ��
	"�׷��� ����"�� ����ϴ� ��Ʈ�� �����ٰ� �� �� ������
	
	�̴� �� �ϳ��� ������Ʈ�� ������ �� ������ ����ϴ� �Ժ� Ŭ�����μ� ����
	�ش� ������Ʈ�� �����ϴ� ������ �����ϰ� ��

	���ݺ��� ���� Shape��� Ŭ������
	�� "�׷���"�� ����Ѵٴ� ���� ���� �ǹ������� ü���ϱ� ���ؼ� ����ϴ� Ŭ����

	��, �� Ŭ������ �������� 3D �׷��Ƚ� �̷��� �������� �ʰ� ����� �ӽ� Ŭ����
	������ �ܱⰣ ���ȸ� ����ϰ� �� �ڿ��� �籸���� ����
*/

class Shape
{
protected:
	vector<Vertex> vertices = {};
	// Vertex�� �����ϴ� vector�� �����ξ�,
	// �� ������ ��µǴ� �� ����� ������ ������ �ڷᱸ���� ����

	float pos_x, pos_y; //@
	// ������ ��ġ�� ����ص� ����
	// (�̹����� ����ϰ�, ���������� 3D �׷��� �̷��� ������ �� ������ ���)
	// ������ �̷� ������ �ڿ� ���ַ� @ ǥ��

	ID3D11Buffer* VB; //@
	// ���� ������ �׷��� ��¿� �ʿ��� �����͸� �˾Ƽ� �����ϵ���,
	// �� ��ü�� ����� ���۸� �����ϵ��� �����

public:
	Shape(float x, float y);
	~Shape();

	ID3D11Buffer** const GetBuffer() { return &VB; }
	int GetVertexSize() { return vertices.size(); }
};