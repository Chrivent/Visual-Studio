#pragma once

// ���� �츮�� ����� ������Ʈó��
// ���� �ڵ� �ʿ��� ��� �۾��� ������� �ʰ�,
// ���α׷��� �������� ó���� ����ϴ� Ŭ������ �ϳ� ����
// �ű⼭ ���α׷��� �ʿ��� �۾����� �����ϴ� ���� �Ѱ��ϵ��� ����� �������
// ���α׷��� �����Ѵ� ��찡 ����

// �׷��� �� ���α׷��� �������� �帧�� ����ϴ� �� Ŭ������ �̸���
// Program�̶� ���� ��
// ��, �� Ŭ������ ���α׷��� �������� ó���� �Ѱ��ϴ� Ŭ����

class Program
{
private:
	Scene* scene;
	// ���α׷����� �ϳ��� ����� ����ϴ� Ŭ����
	// �� Ŭ������ ���� �츮�� ���� ȭ�鿡�� ��µǴ� ������� ���� ����

public:
	Program();
	~Program();

	void Update(); // ���α׷��� ����Ǹ鼭 ������Ʈ�Ǿ�� �� ������� ����

	void Render(); //			''		  ȭ�鿡 ��µ� �������
				   // �� �Լ����� ���þ� ����ϵ��� ��

	void Create();
	// �� Ŭ������ ���鶧 �ʱ�ȭ�ؾ� �ϴ� ������� �����ڿ��� �и��ؼ� ����

	void Delete();
	// �� Ŭ������ ����� ����Ǿ��� �� ó���ؾ� �ϴ� �������
	// �Ҹ��ڿ��� �и��ؼ� �����, �ܺο��� ȣ���� ������ ���·� ����
};