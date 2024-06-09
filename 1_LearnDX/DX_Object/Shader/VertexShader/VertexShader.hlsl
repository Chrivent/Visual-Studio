cbuffer world : register(b0)
{
	matrix world;
}
cbuffer view : register(b1)
{
	matrix view;
}
cbuffer projection : register(b2)
{
	matrix projection;
}
// 위 3개의 Const Buffer(=상수 버퍼)는
// WVP 변환을 하기 위해 입력받아야 하는 버퍼

// world 행렬을 b0라는 슬롯을 통해 입력받겠다
// view 행렬을 b1이라는 슬롯을 통해 입력받겠다
// projection 행렬을 b2라는 슬롯을 통해 입력받겠다
// 라고, 셰이더가 입력받을 슬롯을 정의하는 구문

// 이렇게 셰이더 측에 어느 슬롯을 통해 데이터를 받을 것인지 설정해두면
// 이후 메인 프로젝트(코드) 쪽에서 어느 슬롯에 데이터를 보냈다고 명시하고 보내기만 하면
// 셰이더에서 알아서 해당 데이터를 받아 이후의 처리를 진행함

struct VertexInput
{
	float4 pos : POSITION;
	float4 color : COLOR;
};

struct PixelInput
{
	float4 position : SV_Position;
	float4 color : COLOR;
};


PixelInput VS(VertexInput input)
{
	PixelInput output;
	
	// 앞으로는 여기서 지금까지 입력된 데이터들을 이용해
	// WVP 변환을 수행함
	
	output.position = mul(input.pos, world);
	// mul : HLSL에서 지원하는 행렬끼리의 곱셈을 수행해주는 함수
	// 정확히는 벡터 X 행렬의 곱셈을 수행하는 함수
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	
	// 위 3개는 각각 World 변환, View 변환, Projection 변환을 수행하는 코드들
	
	output.color = input.color;

	return output;	
	
}
