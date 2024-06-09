#include "framework.h"
#include "Star.h"

Star::Star(float x, float y, D3D11_PRIMITIVE_TOPOLOGY S) : Shape(x, y), type(S)
{
	vertices.emplace_back(0.0f, +0.8f, 1.0f, 0.0f, 0.0f);
	vertices.emplace_back(+0.05f, +0.5f, 1.0f, 1.0f, 0.0f);
	vertices.emplace_back(-0.05f, +0.5f, 1.0f, 1.0f, 0.0f);

	vertices.emplace_back(+0.25f, +0.5f, 1.0f, 1.0f, 0.0f);
	vertices.emplace_back(+0.08f, +0.3f, 1.0f, 1.0f, 0.0f);
	vertices.emplace_back(+0.05f, +0.5f, 1.0f, 1.0f, 0.0f);

	vertices.emplace_back(+0.15f, -0.1f, 1.0f, 1.0f, 0.0f);
	vertices.emplace_back(0.0f, +0.1f, 1.0f, 1.0f, 0.0f);
	vertices.emplace_back(+0.08f, +0.3f, 1.0f, 1.0f, 0.0f);

	vertices.emplace_back(-0.15f, -0.1f, 1.0f, 1.0f, 0.0f);
	vertices.emplace_back(-0.08f, +0.3f, 1.0f, 1.0f, 0.0f);
	vertices.emplace_back(0.0f, +0.1f, 1.0f, 1.0f, 0.0f);

	vertices.emplace_back(-0.25f, +0.5f, 1.0f, 1.0f, 0.0f);
	vertices.emplace_back(-0.05f, +0.5f, 1.0f, 1.0f, 0.0f);
	vertices.emplace_back(-0.08f, +0.3f, 1.0f, 1.0f, 0.0f);

	vertices.emplace_back(-0.05f, +0.5f, 1.0f, 1.0f, 0.0f);
	vertices.emplace_back(+0.05f, +0.5f, 1.0f, 1.0f, 0.0f);
	vertices.emplace_back(-0.08f, +0.3f, 1.0f, 1.0f, 0.0f);

	vertices.emplace_back(+0.05f, +0.5f, 1.0f, 1.0f, 0.0f);
	vertices.emplace_back(+0.08f, +0.3f, 1.0f, 1.0f, 0.0f);
	vertices.emplace_back(-0.08f, +0.3f, 1.0f, 1.0f, 0.0f);

	vertices.emplace_back(-0.08f, +0.3f, 1.0f, 1.0f, 0.0f);
	vertices.emplace_back(+0.08f, +0.3f, 1.0f, 1.0f, 0.0f);
	vertices.emplace_back(0.0f, +0.1f, 1.0f, 1.0f, 0.0f);

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * vertices.size();

	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices.data();

	Device::Get()->GetDevice()
		->CreateBuffer(&bd, &initData, &VB);
}
