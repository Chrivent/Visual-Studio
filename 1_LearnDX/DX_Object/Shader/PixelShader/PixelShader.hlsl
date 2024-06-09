cbuffer Color : register(b0)
{
	float4 color;
}
// VS 측과 마찬가지로 메인 프로젝트 쪽에서
// 버퍼를 픽셀 셰이더에 입력할 경우 이 슬롯을 통해 입력된다는 것을 명시

struct PixelInput
{
	float4 position : SV_Position;
	float4 color : COLOR;
};


float4 PS(PixelInput input) : SV_TARGET
{
	return input.color * color;
	// 지금까진 앞의 input.color만 이용해서 색을 출력했는데
	// 이제부턴 입력받은 색 버퍼의 값까지 고려해 색상을 출력한다는 코드
}
