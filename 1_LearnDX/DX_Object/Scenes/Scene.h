#pragma once
/*
	�����̶�� �ϴ� ���� ��� �����Ǿ� �ִ°�?�� �ٺ������� �����غ���

	ex| ��ũ �ҿ��� ���, ������ ������ ����Ǵ� 3D ������ ����ϴ� ����
	    �κ��丮�� �ѹ� ������� �� ȭ�鿡 �κ��丮�� ������ ǥ��� ��

		�׷��� �κ��丮�� �����ִ� ���߿��� ���� ��ü�� �ǽð����� ��� ����ǰ� ����
		�κ��丮���� �������� ���� ���� ������ ���ݴ��ϸ� â�� �����ִ� ��Ȳ�ε�
		ü���� �ǽð����� �����ϴ� �� ���������� ������ ��� ����Ǵ� �� Ȯ�� ����
		-> �κ��丮�� ���� â�� �� 3D ������ ǥ���ϴ� �׷��� ���� ���� ��µǰ� �ִٴ� �ǹ�

		�׷��ٸ� �� ���� ��� ���� ȭ�鿡�� ���� ����� ������ �� ���� ȭ���̶� �� �� ����
		�� ���� ���������� ������ �ٸ� ���̶� �� �� �ִ°�?
		-> �ٺ������δ� �� �� �Ȱ��� "���� ȭ��"�̶�� �������� ������ ����
		   ������ 3D �������� �ٷ�� ���� �÷��� ȭ���̰�,
		   �ٸ� �� ���� �κ��丮�� �ٷ�� ���� ȭ���̶� �� �� ����
		   ��� ���̰� ������Ʈ ��ȭ ������ �´� ��ɵ��� �����Ǿ� �ִ� �ϳ��� ȭ��

	�̷� ������, ������ �⺻������ "ȭ��" ������ ������
	���� ���� �÷��̸� ����ϴ� ȭ���� ���� �ְ�
	�κ��丮�� ����ϴ� ȭ���� ���� ������
	������ ����ϴ� ȭ�� ���� ���� ����

	������̰� ���� ȭ���̴�
	�� ȭ��� ��ü�� ����� �������� �Ǿ��־�� �̷� ȭ����� ���� ������ �� ���� ��
	�׷��� ȭ���� ����ϴ� �θ� Ŭ���� ��ü�� �����,
	���� ������ �����ϴ� ȭ����� ����ϰ� �� Ŭ�������� �̸� ��ӽ��Ѽ� ������
*/

class Scene
{
protected:
	VertexShader* VS;
	PixelShader* PS;
	// ������ ����� Scene���� �����ϱ� ������ ���⼭ ������� ��������,
	// �����δ� �츮�� ���� �� ������Ʈ�� �˾Ƽ� ����� ����� ����

public:
	// ��ӿ� Ŭ�����̹Ƿ� ��� �Լ��� ���� �Լ�
	virtual ~Scene() {};
	// �Ҹ��� ��쿣 �ݵ�� �����α�� �ؾ��ϴ� �׳� ���� �Լ���

	virtual void Update() = 0;
	virtual void Render() = 0;
	// �ڽ� Ŭ�������� �ݵ�� ������ �ϴ�
	// ������Ʈ / ��� �Լ��� ���� �����Լ��� ����
};

// Scene : �������� �ǹ̷� ������ "���"�̶� ��
// ���� ���α׷��ֿ����� "�ּ� �ϳ��� ���� ������ �̷����� ����"�̶�� �ǹ̷� ����
// �����̳� ������ �� ���� ���� ���� ȭ�� � �ϳ��� Scene���� ���
// -> ���� ���α׷����� �⺻������ ���� Scene�� ���� 
// ������ Scene�� ������ Ư�� �ܰ踦 �õ��� �����ϰ�,
// �ʿ信 ���� �� Scene�� ��ü�ؼ� ����Ͽ� ������ �����Ű�� ������ ����� ����

// �� Scene�̶�� Ŭ������ �׷� Scene�� ���� �� ����� �������̽��� ���� ��