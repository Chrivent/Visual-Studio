#pragma once

class VertexShader
	// 말 그대로 정점 셰이더를 담당할 클래스
	// -> DX에서 제공하는 정점 셰이더와 관련된 클래스들을
	// 손쉽게 생성하고 세팅하기 위한 클래스
{
private:
	ID3D11VertexShader* VS;
	// 실제 DX에서의 정점 셰이더를 담당하는 VS
	ID3D11InputLayout* input_layout;
	// 그 정점 셰이더에 들어갈 데이터가 어떻게 생겼는지를 정의하는 클래스

public:
	VertexShader(LPCWSTR file_loc, DWORD flags);
	// 매개 변수로 문자열과 셰이더 설정에 필요한 플래그를 받는다
	~VertexShader();

	void Release();
	ID3D11InputLayout* GetInputLayout() { return input_layout; }
	ID3D11VertexShader* GetVertexShader() { return VS; }
};