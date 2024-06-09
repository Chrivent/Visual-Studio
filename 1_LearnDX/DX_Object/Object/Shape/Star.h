#pragma once

class Star : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;

public:
	Star(float x = 0, float y = 0, D3D11_PRIMITIVE_TOPOLOGY S = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
};

