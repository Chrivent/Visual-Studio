#pragma once
class PixelShader
{
private:
	ID3D11PixelShader* PS;

public:
	PixelShader(LPCWSTR file_loc, DWORD flags);
	// LPCWSTR = WCHAR = �����ڵ� �����ϴ� ���� �ڷ���
	~PixelShader();

	void Release();
	ID3D11PixelShader* GetPixelShader() { return PS; }

};