#include <iostream>
#include <DirectXMath.h>

using namespace DirectX;

void PrintMatrix(const XMMATRIX& m)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << m.r[i].m128_f32[j] << " ";
		std::cout << std::endl;
	}
}

int main()
{
	XMVECTOR axisVector = XMVectorSet(1, 1, 1, 1);
	axisVector = DirectX::XMVector3Normalize(axisVector);
	XMVECTOR qQuat = DirectX::XMQuaternionRotationAxis(axisVector, XMConvertToRadians(45.0f));
	std::cout << "qQuat : " << qQuat.m128_f32[0] << ", "
		<< qQuat.m128_f32[1] << ", "
		<< qQuat.m128_f32[2] << ", "
		<< qQuat.m128_f32[3] << "\n";

	{
		float thetaDegrees = 45.0f;
		DirectX::XMVECTOR v = XMVectorSet(0, 0, 1, 0);
		DirectX::XMVECTOR n = XMVectorSet(1, 1, 1, 0);
		n = DirectX::XMVector3Normalize(n);

		float theta = DirectX::XMConvertToRadians(thetaDegrees);

		float cosTheta = cosf(theta);
		float sinTheta = sinf(theta);

		DirectX::XMVECTOR vRotated =
			cosTheta * v +
			(1 - cosTheta) * DirectX::XMVector3Dot(n, v) * n +
			sinTheta * DirectX::XMVector3Cross(n, v);

		std::cout << "vRotated : " << vRotated.m128_f32[0] << ", "
			<< vRotated.m128_f32[1] << ", "
			<< vRotated.m128_f32[2] << ", "
			<< vRotated.m128_f32[3] << "\n";
	}

	XMVECTOR qRotQuat = DirectX::XMQuaternionRotationAxis(axisVector, XMConvertToRadians(45.0f));
	XMMATRIX RotMat = DirectX::XMMatrixRotationQuaternion(qRotQuat);
	PrintMatrix(RotMat);

	std::cout << "vRotated" << std::endl;

	XMMATRIX RotMatAxisAngle = DirectX::XMMatrixRotationAxis(axisVector, XMConvertToRadians(45.0f));
	PrintMatrix(RotMat);

	float q1 = qRotQuat.m128_f32[0];
	float q2 = qRotQuat.m128_f32[1];
	float q3 = qRotQuat.m128_f32[2];
	float q4 = qRotQuat.m128_f32[3];

	float m00 = 1 - 2 * q2 * q2 - 2 * q3 * q3;
	float m01 = 2 * q1 * q2 + 2 * q3 * q4;
	float m02 = 2 * q1 * q3 - 2 * q2 * q4;

	float m10 = 2 * q1 * q2 - 2 * q3 * q4;
	float m11 = 1 - 2 * q1 * q1 - 2 * q3 * q3;
	float m12 = 2 * q2 * q3 + 2 * q1 * q4;

	float m20 = 2 * q1 * q3 + 2 * q2 * q4;
	float m21 = 2 * q2 * q3 - 2 * q1 * q4;
	float m22 = 1 - 2 * q1 * q1 - 2 * q2 * q2;

	std::cout << "Direct Rotated 1 " << m00 << ", " << m01 << ", " << m02 << std::endl;
	std::cout << "Direct Rotated 2 " << m10 << ", " << m11 << ", " << m12 << std::endl;
	std::cout << "Direct Rotated 3 " << m20 << ", " << m21 << ", " << m22 << std::endl;
}