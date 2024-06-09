#include "framework.h"

Program::Program()
{
	Create();
	scene = new ObjectTrialScene();
	// �ٷ� �� �κ��� ���� ���α׷��� � Scene�� ����� �������� ����
	// DX�� �ٷ�� �ʹ� ���������� Scene�� ���ƺ��� �ϳ��� ����� ���̹Ƿ�
	// �� Scene�� ���⼭ �����ϰ�, ���߿� �ʿ��ϸ� ���� Scene�� ���� ä
	// ���ο� Scene�� ���⿡ ����ؼ� ����ϴ� ������ ���α׷��� ������ ����
}

Program::~Program()
{
	delete scene;
}

void Program::Update()
{
	scene->Update();
}

void Program::Render()
{
	Device::Get()->Clear();
	// ������ ���α׷����� Render �Լ��� ȣ��Ǿ��� �� �̷����� ������
	// ���� ������ Scene�� �� ���� �ϳ��� �ٷ�� ������
	// �׸��� Scene ���ο��� �� ȭ�� �ʱ�ȭ�� �ϱ� ������ ���⼭�� ����
	scene->Render();
	Device::Get()->Present();

}

void Program::Create()
{
	Device::Get(); // �̱����� ���⼭ ����
}

void Program::Delete()
{
	Device::Delete();
}
