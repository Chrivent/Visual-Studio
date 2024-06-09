#include "framework.h"
#include "ObjectTrialScene.h"

ObjectTrialScene::ObjectTrialScene()
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	// ���̴� ������ �ʿ��� �÷��׸� �̸� ����

	VS = new VertexShader(L"Shader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"Shader/VertexShader.hlsl", flags);
	// ���� ���̴��� �ȼ� ���̴��� ���̴� �ּҰ� �ִ� ���Ͽ� ����
	// �߰���, ������ζ�� �� ���̴����� ���̴��� �̿��ؼ� ����� ������ ����ϴ�
	// Ŭ���� �� ��ü�� ������ �־�� �� �����̳�
	// �̹� �ð������� �״�� �� �ʿ��� �̿���

	// ������� ������ ������ ��������

	t = new Triangle(0.5f, 0.5f);
	s = new Star(0.0f, 0.0f);
}

ObjectTrialScene::~ObjectTrialScene()
{
	delete t;
	delete s;
	delete VS;
	delete PS;
}

void ObjectTrialScene::Update()
{
}

void ObjectTrialScene::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;


	DVC->VSSetShader(VS->GetVertexShader(), nullptr, 0);
	DVC->PSSetShader(PS->GetPixelShader(), nullptr, 0);
	// ����̽��� ���� ���̴��� �ȼ� ���̴��� ����
	// �̷��� DeviceContext�� ������ ���� ������
	// �̸� �ҷ����� �ڵ�� �״�� ���°� �ʹ� �� ��ȿ����
	// �׷��� ��ũ�θ� �����Ͽ� �̸� �ִ��� ª�� ���� ��

	DVC->IASetInputLayout(VS->GetInputLayout());
	// �� Scene�� ����ϰ� �ִ� VS�� ���ο� �ִ� input_layout�� ������
	// device_context�� ����, ������ � �ڷᰡ ���̴��� �Ѿ����
	// ��ġ�� �˸�

	DVC->IASetVertexBuffers(0, 1, t->GetBuffer(), &stride, &offset);
	DVC->IASetVertexBuffers(0, 1, s->GetBuffer(), &stride, &offset);
	// �ﰢ���� ����Ѵ� �ν��Ͻ��� t�� ������ �ִ� ������
	// ����Ǿ� �ִ� ���۸� ����̽��� ����

	DVC->IASetPrimitiveTopology(t->GetType());
	DVC->IASetPrimitiveTopology(s->GetType());
	// �ﰢ���� �����ϰ� �ִ� ������ �׸� ����� ����̽��� ����

	DVC->Draw(t->GetVertexSize(), 0);
	DVC->Draw(s->GetVertexSize(), 0);
	// �غ� �� �������� ����̽��� ���ݱ��� �Է��ߴ� �����͵��� ���� �׷���
}
