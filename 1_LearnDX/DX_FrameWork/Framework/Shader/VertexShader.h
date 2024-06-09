#pragma once

class VertexShader
	// �� �״�� ���� ���̴��� ����� Ŭ����
	// -> DX���� �����ϴ� ���� ���̴��� ���õ� Ŭ��������
	// �ս��� �����ϰ� �����ϱ� ���� Ŭ����
{
private:
	ID3D11VertexShader* VS;
	// ���� DX������ ���� ���̴��� ����ϴ� VS
	ID3D11InputLayout* input_layout;
	// �� ���� ���̴��� �� �����Ͱ� ��� ��������� �����ϴ� Ŭ����

public:
	VertexShader(LPCWSTR file_loc, DWORD flags);
	// �Ű� ������ ���ڿ��� ���̴� ������ �ʿ��� �÷��׸� �޴´�
	~VertexShader();

	void Release();
	ID3D11InputLayout* GetInputLayout() { return input_layout; }
	ID3D11VertexShader* GetVertexShader() { return VS; }
};