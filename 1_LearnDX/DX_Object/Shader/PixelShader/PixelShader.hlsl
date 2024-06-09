cbuffer Color : register(b0)
{
	float4 color;
}
// VS ���� ���������� ���� ������Ʈ �ʿ���
// ���۸� �ȼ� ���̴��� �Է��� ��� �� ������ ���� �Էµȴٴ� ���� ���

struct PixelInput
{
	float4 position : SV_Position;
	float4 color : COLOR;
};


float4 PS(PixelInput input) : SV_TARGET
{
	return input.color * color;
	// ���ݱ��� ���� input.color�� �̿��ؼ� ���� ����ߴµ�
	// �������� �Է¹��� �� ������ ������ ����� ������ ����Ѵٴ� �ڵ�
}
