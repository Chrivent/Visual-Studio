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
// �� 3���� Const Buffer(=��� ����)��
// WVP ��ȯ�� �ϱ� ���� �Է¹޾ƾ� �ϴ� ����

// world ����� b0��� ������ ���� �Է¹ްڴ�
// view ����� b1�̶�� ������ ���� �Է¹ްڴ�
// projection ����� b2��� ������ ���� �Է¹ްڴ�
// ���, ���̴��� �Է¹��� ������ �����ϴ� ����

// �̷��� ���̴� ���� ��� ������ ���� �����͸� ���� ������ �����صθ�
// ���� ���� ������Ʈ(�ڵ�) �ʿ��� ��� ���Կ� �����͸� ���´ٰ� ����ϰ� �����⸸ �ϸ�
// ���̴����� �˾Ƽ� �ش� �����͸� �޾� ������ ó���� ������

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
	
	// �����δ� ���⼭ ���ݱ��� �Էµ� �����͵��� �̿���
	// WVP ��ȯ�� ������
	
	output.position = mul(input.pos, world);
	// mul : HLSL���� �����ϴ� ��ĳ����� ������ �������ִ� �Լ�
	// ��Ȯ���� ���� X ����� ������ �����ϴ� �Լ�
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	
	// �� 3���� ���� World ��ȯ, View ��ȯ, Projection ��ȯ�� �����ϴ� �ڵ��
	
	output.color = input.color;

	return output;	
	
}
